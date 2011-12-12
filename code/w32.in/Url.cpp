// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.in/Url.hpp>
#include <w32/Error.hpp>

namespace {

    ::DWORD length ( ::LPCWSTR url, ::DWORD flags )
    {
        ::DWORD size = 0;
        const ::BOOL result =
            ::InternetCanonicalizeUrlW(url, 0, &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != ERROR_INSUFFICIENT_BUFFER )
            {
                UNCHECKED_WIN32C_ERROR(InternetCanonicalizeUrl, error);
            }
        }
        return (size);
    }

    void canonicalize
        ( ::LPCWSTR url, ::LPWSTR encoded, ::DWORD size, ::DWORD flags )
    {
        const ::BOOL result =
            ::InternetCanonicalizeUrlW(url, encoded, &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetCanonicalizeUrl, error);
        }
    }

    ::DWORD length ( ::LPCWSTR base, ::LPCWSTR path, ::DWORD flags )
    {
        ::DWORD size = 0;
        const ::BOOL result =
            ::InternetCombineUrlW(base, path, 0, &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != ERROR_INSUFFICIENT_BUFFER )
            {
                UNCHECKED_WIN32C_ERROR(InternetCombineUrlW, error);
            }
        }
        return (size);
    }

    void combine ( ::LPCWSTR base, ::LPCWSTR path,
        ::LPWSTR combined, ::DWORD size, ::DWORD flags )
    {
        const ::BOOL result =
            ::InternetCombineUrlW(base, path, combined, &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetCombineUrl, error);
        }
    }

    const ::DWORD ENCODE = ICU_ENCODE_PERCENT;
    const ::DWORD DECODE = ICU_DECODE;
    const ::DWORD BYPASS = ICU_NO_ENCODE;

}

namespace w32 { namespace in {

    string Url::encode ( const string& url )
    {
        string result(::length(url.data(), ENCODE));
        ::canonicalize(url.data(), result.data(), result.size(), ENCODE);
        return (result);
    }

    string Url::decode ( const string& url )
    {
        string result(::length(url.data(), DECODE));
        ::canonicalize(url.data(), result.data(), result.size(), DECODE);
        return (result);
    }

    string join ( const string& base, const string& path )
    {
        string result(::length(base.data(), path.data(), DECODE));
        ::combine(base.data(), path.data(),
            result.data(), result.size(), DECODE);
        return (result);
    }

    Url::Url ( const string& url )
    {
            // Clear structure.
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwStructSize = sizeof(myData);
        
            // Select components to parse.
        myData.dwSchemeLength    = 1;
        myData.dwHostNameLength  = 1;
        myData.dwUserNameLength  = 1;
        myData.dwPasswordLength  = 1;
        myData.dwUrlPathLength   = 1;
        myData.dwExtraInfoLength = 1;
         
        const ::BOOL result = ::InternetCrackUrlW
            (url.data(), url.size(), 0, &myData);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetCrackUrl, error);
        }
    }

    const Url::Data& Url::data () const
    {
        return (myData);
    }

    string Url::scheme () const
    {
        return (string(myData.lpszScheme, myData.dwSchemeLength));
    }

    string Url::username () const
    {
        return (string(myData.lpszUserName, myData.dwUserNameLength));
    }

    string Url::password () const
    {
        return (string(myData.lpszPassword, myData.dwPasswordLength));
    }

    string Url::host () const
    {
        return (string(myData.lpszHostName, myData.dwHostNameLength));
    }

    Port Url::port () const
    {
        return (myData.nPort);
    }

    string Url::path () const
    {
        return (string(myData.lpszUrlPath, myData.dwUrlPathLength));
    }

    string Url::query () const
    {
        return (string(myData.lpszExtraInfo, myData.dwExtraInfoLength));
    }

} }
