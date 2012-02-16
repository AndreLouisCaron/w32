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

#include <w32.cr/Blob.hpp>
#include <w32.cr/Provider.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>
#include <algorithm>

namespace {

    ::DWORD getlhssize ( const ::WCHAR * rhsdata, ::DWORD rhssize )
    {
        ::DWORD lhssize = 0;
        const ::BOOL result = ::CryptStringToBinaryW(
            rhsdata, rhssize, CRYPT_STRING_HEXRAW, 0, &lhssize, 0, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptStringToBinary, error);
        }
        return (lhssize);
    }

    ::DWORD getlhssize ( const ::BYTE * rhsdata, ::DWORD rhssize )
    {
        ::DWORD lhssize = 0;
        const ::BOOL result = ::CryptBinaryToStringW(
            rhsdata, rhssize, CRYPT_STRING_HEXRAW, 0, &lhssize);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptBinaryToString, error);
        }
        return (lhssize);
    }

}

namespace w32 { namespace cr {

    Blob::Blob ( dword size )
        : mySize(size), myData(new byte[mySize])
    {
    }

    Blob::Blob ( dword size, const void * data )
        : mySize(size), myData(new byte[mySize])
    {
        ::CopyMemory(myData, data, mySize);
    }

    Blob::Blob ( const Blob& other )
        : mySize(other.mySize), myData(new byte[mySize])
    {
        ::CopyMemory(myData, other.myData, mySize);
    }

    dword Blob::size () const
    {
        return (mySize);
    }

    byte * Blob::data ()
    {
        return (myData);
    }

    const byte * Blob::data () const
    {
        return (myData);
    }

    void Blob::swap ( Blob& rhs )
    {
        std::swap(mySize, rhs.mySize);
        std::swap(myData, rhs.myData);
    }

    void Blob::truncate ( dword size )
    {
        mySize = std::min(mySize, size);
    }

    Blob& Blob::operator= ( const Blob& rhs )
    {
        Blob tmp(rhs); tmp.swap(*this); return (*this);
    }

    const Format Format::hex ()
    {
        return (CRYPT_STRING_HEX);
    }

    const Format Format::hexraw ()
    {
        return (CRYPT_STRING_HEXRAW);
    }

    const Format Format::hexascii ()
    {
        return (CRYPT_STRING_HEXASCII);
    }

    const Format Format::base64 ()
    {
        return (CRYPT_STRING_BASE64);
    }

    const Format Format::base64certificate ()
    {
        return (CRYPT_STRING_BASE64HEADER);
    }

    const Format Format::base64request ()
    {
        return (CRYPT_STRING_BASE64REQUESTHEADER);
    }

    const Format Format::base64x509 ()
    {
        return (CRYPT_STRING_BASE64X509CRLHEADER);
    }

#ifdef CRYPT_STRING_STRICT
    const Format Format::asn1 ()
    {
        return (CRYPT_STRING_STRICT);
    }
#endif

    Format::Format ( Value value )
        : myValue(value)
    {
    }

    Format::operator Format::Value () const
    {
        return (myValue);
    }

    string convert ( const Blob& rhs, const Format& format )
    {
        ::DWORD lhssize = ::getlhssize(rhs.data(), rhs.size());
        string lhs(lhssize);
        const ::BOOL result = ::CryptBinaryToStringW(
            rhs.data(), rhs.size(), format, lhs.data(), &lhssize
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptHashData, error);
        }
        return (lhs);
    }

    Blob convert ( const string& rhs, const Format& format )
    {
        ::DWORD lhssize = ::getlhssize(rhs.data(), rhs.size());
        Blob lhs(lhssize);
        const ::BOOL result = ::CryptStringToBinaryW(
            rhs.data(), rhs.size(), format, lhs.data(), &lhssize, 0, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptHashData, error);
        }
        return (lhs);
    }

    void random ( const Provider& provider, void * data, dword size )
    {
        const ::BOOL result = ::CryptGenRandom(
            provider.handle(), size, static_cast<::BYTE*>(data));
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGenRandom, error);
        }
    }

} }
