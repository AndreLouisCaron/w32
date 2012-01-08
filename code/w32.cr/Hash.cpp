// Copyright(c) Andre Caron, 2009-2012
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.cr/Hash.hpp>
#include <w32.cr/Blob.hpp>
#include <w32.cr/Key.hpp>
#include <w32.cr/Provider.hpp>
#include <w32/Error.hpp>
#include <w32/astring.hpp>
#include <w32/string.hpp>
#include <string>

namespace {

    ::HCRYPTHASH acquire ( ::HCRYPTPROV provider, ::DWORD type )
    {
        ::HCRYPTHASH handle = 0;
        const ::BOOL result = ::CryptCreateHash
            (provider, type, 0, 0, &handle);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptCreateHash, error);
        }
        return (handle);
    }

    void abandon ( ::HCRYPTHASH object ) {}
    void release ( ::HCRYPTHASH object )
    {
        const ::BOOL result = ::CryptDestroyHash(object);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptDestroyHash, error);
        }
    }

    void getparam ( ::HCRYPTHASH hash, ::DWORD key,
        void * data, ::DWORD& size, ::DWORD flags=0 )
    {
        const ::BOOL result = ::CryptGetHashParam
            (hash, key, static_cast<::BYTE*>(data), &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGetHashParam, error);
        }
    }

}

namespace w32 { namespace cr {

    const Hash::Handle Hash::claim ( ::HCRYPTHASH object )
    {
        return (Handle(object, &::release));
    }

    const Hash::Handle Hash::proxy ( ::HCRYPTHASH object )
    {
        return (Handle(object, &::abandon));
    }

    Hash::Hash ( const Provider& provider, const Type& type )
        : myHandle(claim(::acquire(provider.handle(), type)))
    {
    }

    const Hash::Handle& Hash::handle () const
    {
        return (myHandle);
    }

    void Hash::put ( const void * data, dword size )
    {
        const ::BOOL result = ::CryptHashData(
            handle(), static_cast<const ::BYTE*>(data), size, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptHashData, error);
        }
    }

    void Hash::put ( const Key& key )
    {
        const ::BOOL result = ::CryptHashSessionKey(handle(), key.handle(), 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptHashSessionKey, error);
        }
    }

    Blob Hash::data () const
    {
        Blob lhs(size());
        ::DWORD lhssize = lhs.size();
        const ::BOOL result = ::CryptGetHashParam(
            handle(), HP_HASHVAL, lhs.data(), &lhssize, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptHashData, error);
        }
	lhs.truncate(lhssize);
        return (lhs);
    }

    const Hash::Type Hash::type () const
    {
        return (Type::of(*this));
    }

    dword Hash::size () const
    {
        ::DWORD data = 0;
        ::DWORD size = 4;
        ::getparam(handle(), HP_HASHSIZE, &data, size);
        return (data);
    }

    bool Hash::verify ( const Key& key, const Blob& signature )
    {
        const ::BOOL result = ::CryptVerifySignatureW(
            handle(), signature.data(), signature.size(), key.handle(), 0, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == NTE_BAD_SIGNATURE ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(CryptHashData, error);
        }
        return (true);
    }

    const Hash::Type Hash::Type::md2 ()
    {
        return (CALG_MD2);
    }

    const Hash::Type Hash::Type::md4 ()
    {
        return (CALG_MD4);
    }

    const Hash::Type Hash::Type::md5 ()
    {
        return (CALG_MD5);
    }

    const Hash::Type Hash::Type::rc2 ()
    {
        return (CALG_RC2);
    }

    const Hash::Type Hash::Type::sha1 ()
    {
        return (CALG_SHA1);
    }

    const Hash::Type Hash::Type::sha256 ()
    {
        return (CALG_SHA_256);
    }

    const Hash::Type Hash::Type::sha384 ()
    {
        return (CALG_SHA_384);
    }

    const Hash::Type Hash::Type::sha512 ()
    {
        return (CALG_SHA_512);
    }

    const Hash::Type Hash::Type::of ( const Hash& hash )
    {
        ::DWORD data = 0;
        ::DWORD size = 4;
        ::getparam(hash.handle(), HP_ALGID, &data, size);
        return (data);
    }

    Hash::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Hash::Type::operator Hash::Type::Value () const
    {
        return (myValue);
    }

    Hash md5 ( const Provider& provider, const void * data, dword size )
    {
        Hash hash(provider, Hash::Type::md5());
	hash.put(data, size);
        return (hash);
    }

    Hash sha1 ( const Provider& provider, const void * data, dword size )
    {
        Hash hash(provider, Hash::Type::sha1());
	hash.put(data, size);
        return (hash);
    }

} }
