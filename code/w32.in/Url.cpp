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
