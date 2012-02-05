// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Environment.hpp>
#include <w32/Error.hpp>
#include <algorithm>
#include <functional>

namespace {

    ::DWORD length ( ::LPCWSTR variable )
    {
        ::WCHAR dummy[] = L"";
        const ::DWORD result = ::GetEnvironmentVariableW(variable, dummy, 0);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ENVVAR_NOT_FOUND )
            {
                return (0);
            }
            UNCHECKED_WIN32C_ERROR(GetEnvironmentVariable, error);
        }
        return (result);
    }

    void fetch ( ::LPCWSTR variable, ::LPWSTR buffer, ::DWORD length )
    {
        const ::DWORD result =
            ::GetEnvironmentVariableW(variable, buffer, length);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ENVVAR_NOT_FOUND )
            {
            }
            UNCHECKED_WIN32C_ERROR(GetEnvironmentVariable, error);
        }
    }

        // Environment block is allocated with an incompatible memory API.
    struct strings :
        private w32::NotCopyable
    {
        /* data. */
    private:
        const ::LPWCH myData;

        /* construction. */
    public:
        strings ()
            : myData(::GetEnvironmentStringsW())
        {
            if ( myData == 0 ) {
                UNCHECKED_WIN32C_ERROR(GetEnvironmentStrings,::GetLastError());
            }
        }

        ~strings () {
            ::FreeEnvironmentStringsW(myData);
        }

        /* operators. */
    public:
        operator const w32::string () const
        {
            wchar_t * position = myData;
            do {
                while ( *position++ != L'\0' )
                    ;
            }
            while ( *position != L'\0' );
            return (w32::string(myData, position - myData));
        }
    };

        // Predicate for variable look-up.
    struct matches :
        public std::unary_function< const wchar_t*, bool >
    {
        /* data. */
    private:
        const w32::string myName;

        /* construction. */
    public:
        explicit matches ( const w32::string& name )
            : myName(name+L"=")
        {
        }

        /* operators. */
    public:
        result_type operator() ( argument_type candidate ) const
        {
                // Check for name match.
            return (::wcsncmp(myName.data(), candidate, myName.size()) == 0);
        }
    };

}

namespace w32 {

    Environment Environment::empty ()
    {
        static const wchar_t block[] = { L'\0', L'\0' };
        return (Environment(block));
    }

    Environment::Environment ()
        : mstring(::strings())
    {
    }

    Environment::Environment ( const wchar_t * block )
        : mstring(block)
    {
    }

    string Environment::get ( const string& variable )
    {
            // Query required array size.
        const ::DWORD size = ::length(variable.c_str());
        if ( size == 0 ) {
            return (string());
        }
            // Fetch value.
        string result(size);
        ::fetch(variable.c_str(), result.c_str(), result.length());
        return (result);
    }

    string Environment::operator[] ( const string& variable ) const
    {
        const iterator end = mstring::end();
        const iterator match =
            std::find_if(begin(), end, ::matches(variable));
        if (match == end) {
            return (string());
        }
            // Remove "name=" part.
        return (string(::wcschr(*match, L'=')+1));
    }

}
