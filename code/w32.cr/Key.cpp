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

#include <w32.cr/Key.hpp>
#include <w32.cr/Provider.hpp>
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

    ::HCRYPTKEY generate ( ::HCRYPTPROV provider, ::DWORD type, ::DWORD flags )
    {
        ::HCRYPTKEY handle = 0;
        const ::BOOL result = ::CryptGenKey(provider, type, flags, &handle);
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
        return (Key(claim(::generate(provider.handle(), type, 0))));
    }

    Key Key::generate ( const Provider& provider,
                        const Type& type, const Hints& hints )
    {
        return (Key(claim(::generate(provider.handle(), type, hints))));
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

    Key::Hints::Hints ()
        : myValue(0)
    {
    }

    Key::Hints& Key::Hints::exportable ()
    {
        myValue |= CRYPT_EXPORTABLE; return (*this);
    }

    Key::Hints::operator Key::Hints::Value () const
    {
        return (myValue);
    }

} }
