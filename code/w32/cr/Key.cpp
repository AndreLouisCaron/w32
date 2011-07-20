// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/cr/Key.hpp>
#include <w32/cr/Provider.hpp>
#include <w32/Error.hpp>

namespace {

    ::HCRYPTKEY acquire ( ::HCRYPTPROV provider, ::DWORD type )
    {
        ::HCRYPTKEY handle = 0;
        const ::BOOL result = ::CryptGetUserKey(provider, type, &handle);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGetUserKey, error);
        }
        return (handle);
    }

    ::HCRYPTKEY generate ( ::HCRYPTPROV provider, ::DWORD type )
    {
        ::HCRYPTKEY handle = 0;
        const ::BOOL result = ::CryptGenKey(provider, type, 0, &handle);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGenKey, error);
        }
        return (handle);
    }

    ::HCRYPTKEY derive
        ( ::HCRYPTPROV provider, ::HCRYPTHASH hash, ::DWORD algorithm )
    {
        static const ::DWORD flags = CRYPT_EXPORTABLE;
        ::HCRYPTKEY handle = 0;
        const ::BOOL result = ::CryptDeriveKey
            (provider, algorithm, hash, flags, &handle);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptDeriveKey, error);
        }
        return (handle);
    }

    void abandon ( ::HCRYPTKEY object ) {}
    void release ( ::HCRYPTKEY object )
    {
        const ::BOOL result = ::CryptDestroyKey(object);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptDestroyKey, error);
        }
    }

}

namespace w32 { namespace cr {

    const Key::Handle Key::claim ( ::HCRYPTKEY object )
    {
        return (Handle(object, &::release));
    }

    const Key::Handle Key::proxy ( ::HCRYPTKEY object )
    {
        return (Handle(object, &::abandon));
    }

    Key Key::generate ( const Provider& provider, const Type& type )
    {
        return (Key(claim(::generate(provider.handle(), type))));
    }

    Key Key::derive ( const Provider& provider,
        const Hash& hash, const Hash::Type& algorithm )
    {
        return (Key(claim(::derive(provider.handle(), hash.handle(), algorithm))));
    }

    Key::Key ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Key::Key ( const Provider& provider, const Type& type )
        : myHandle(::acquire(provider.handle(), type))
    {
    }

    const Key::Handle& Key::handle () const
    {
        return (myHandle);
    }

    Key::Type Key::Type::exchange ()
    {
        return (AT_KEYEXCHANGE);
    }

    Key::Type Key::Type::signature ()
    {
        return (AT_SIGNATURE);
    }

    Key::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Key::Type::operator Key::Type::Value () const
    {
        return (myValue);
    }

} }
