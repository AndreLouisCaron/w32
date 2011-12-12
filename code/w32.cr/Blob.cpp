// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

#if _WIN32_WINNT > 0x0600
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
