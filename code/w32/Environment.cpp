// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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

    ::DWORD environment_size ( const w32::Environment::Map& environment )
    {
        typedef w32::Environment::Map::const_iterator iterator;

        ::DWORD size = 0;
        iterator current = environment.begin();
        const iterator end = environment.end();
        for (; current != end; ++current) {
            const w32::string& field = current->first;
            const w32::string& value = current->second;
            // count '+' and '\0' delimiters.
            size += field.size() + value.size() + 2;
        }
        // count final '\0' delimiter.
        return (size + 1);
    }

    void copy_environment
        ( const w32::Environment::Map& environment, ::LPWSTR data )
    {
        typedef w32::Environment::Map::const_iterator iterator;

        ::DWORD used = 0;
        iterator current = environment.begin();
        const iterator end = environment.end();
        for (; current != end; ++current) {
            const w32::string& field = current->first;
            const w32::string& value = current->second;
            std::copy(field.begin(), field.end(), data+used);
            data[(used += field.size())++] = L'=';
            std::copy(value.begin(), value.end(), data+used);
            data[(used += value.size())++] = L'\0';
        }
        data[used++] = L'\0';
    }

}

namespace w32 {

    Environment Environment::empty ()
    {
        static const wchar_t block[] = { L'\0', L'\0' };
        return (Environment(block));
    }

    w32::string Environment::format ( const Map& map )
    {
        const dword size = ::environment_size(map);
        const ::LPWSTR data = new ::WCHAR[size];
        ::copy_environment(map, data);
        return (w32::string(w32::string::box(data, size)));
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

    Environment::operator Environment::Map () const
    {
        Map map;
        iterator current = mstring::begin();
        const iterator end = mstring::end();
        for (; (current != end); ++current)
        {
            const wchar_t *const pair = *current;
            std::size_t delimitor = 0;
            while (pair[delimitor] != L'=') {
                ++delimitor;
            }
            w32::string field(pair, delimitor);
            w32::string value(pair+delimitor+1);
            map.insert(std::make_pair(field, value));
        }
        return (map);
    }

}
