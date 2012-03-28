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

/*!
 * @file w32.cr/Provider.cpp
 * @brief Security provider context.
 */

#include <w32.cr/Provider.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>
#include <string>

namespace {

    ::HCRYPTPROV acquire ( ::LPCWSTR container, ::LPCWSTR name,
                           ::DWORD type, ::DWORD flags )
    {
        ::HCRYPTPROV handle = 0;
        const ::BOOL result = ::CryptAcquireContextW
            (&handle, container, name, type, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptAcquireContext, error);
        }
        return (handle);
    }

    void abandon ( ::HCRYPTPROV object ) {}
    void release ( ::HCRYPTPROV object )
    {
        const ::BOOL result = ::CryptReleaseContext(object, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptReleaseContext, error);
        }
    }

    ::DWORD getsize ( ::HCRYPTPROV provider, ::DWORD key, ::DWORD flags=0 )
    {
        ::DWORD size = 0;
        const ::BOOL result = ::CryptGetProvParam
            (provider, key, 0, &size, flags);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGetProvParam, error);
        }
        return (size);
    }

}

namespace w32 { namespace cr {

    const Provider::Handle Provider::claim ( ::HCRYPTPROV object )
    {
        return (Handle(object, &::release));
    }

    const Provider::Handle Provider::proxy ( ::HCRYPTPROV object )
    {
        return (Handle(object, &::abandon));
    }

    Provider::Provider ( const Type& type )
        : myHandle(claim(::acquire(0, MS_DEF_PROV_W, type, 0)))
    {
    }

    Provider::Provider ( const Type& type, const Hints& hints )
        : myHandle(claim(::acquire(0, MS_DEF_PROV_W, type, hints)))
    {
    }

    Provider::Provider ( const Type& type,
                         const Hints& hints, const string& container )
        : myHandle(claim
                   (::acquire(container.data(), MS_DEF_PROV_W, type, hints)))
    {
    }

    const Provider::Handle& Provider::handle () const
    {
        return (myHandle);
    }

    Provider::Type Provider::type () const
    {
        return (Type::of(*this));
    }

    string Provider::name () const
    {
            // Get the size of the result.
        ::DWORD size = ::getsize(handle(), PP_NAME);
        
            // Allocate enough memory.
        std::string name(size+1, '\0');
        
            // Fetch the darn value.
        const ::BOOL result = ::CryptGetProvParam(
            handle(), PP_NAME, (::BYTE*)(name.data()), &size, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGetProvParam, error);
        }
        return (string(name.data(),Codepage::ansi()));
    }

    string Provider::container () const
    {
            // Get the size of the result.
        ::DWORD size = ::getsize(handle(), PP_CONTAINER);
        
            // Allocate enough memory.
        std::string name(size+1, '\0');
        
            // Fetch the darn value.
        const ::BOOL result = ::CryptGetProvParam(
            handle(), PP_CONTAINER, (::BYTE*)(name.data()), &size, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CryptGetProvParam, error);
        }
        return (string(name.data(),Codepage::ansi()));
    }

     const Provider::Type Provider::Type::of ( const Provider& provider )
     {
         ::DWORD type = 0;
         ::DWORD size = sizeof(type);
         const ::BOOL result = ::CryptGetProvParam
             (provider.handle(), PP_PROVTYPE, (::BYTE*)&type, &size, 0);
         if (result == FALSE)
         {
             const ::DWORD error = ::GetLastError();
             UNCHECKED_WIN32C_ERROR(CryptGetProvParam, error);
         }
         return (Type(type));
     }

    const Provider::Type Provider::Type::rsafull ()
    {
        return (PROV_RSA_FULL);
    }

    const Provider::Type Provider::Type::rsaaes ()
    {
        return (PROV_RSA_AES);
    }

    const Provider::Type Provider::Type::rsasig ()
    {
        return (PROV_RSA_SIG);
    }

    const Provider::Type Provider::Type::rsaschannel ()
    {
        return (PROV_RSA_SCHANNEL);
    }

    const Provider::Type Provider::Type::dss ()
    {
        return (PROV_DSS);
    }

    const Provider::Type Provider::Type::dssdh ()
    {
        return (PROV_DSS_DH);
    }

    const Provider::Type Provider::Type::dhschannel ()
    {
        return (PROV_DH_SCHANNEL);
    }

    const Provider::Type Provider::Type::fortezza ()
    {
        return (PROV_FORTEZZA);
    }

    const Provider::Type Provider::Type::msexchange ()
    {
        return (PROV_MS_EXCHANGE);
    }

    const Provider::Type Provider::Type::ssl ()
    {
        return (PROV_SSL);
    }

    Provider::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Provider::Type::operator Provider::Type::Value () const
    {
        return (myValue);
    }

    Provider::Hints::Hints ()
        : myValue(0)
    {
    }

    Provider::Hints& Provider::Hints::verifyContext ()
    {
        myValue |= CRYPT_VERIFYCONTEXT;
        return (*this);
    }

    Provider::Hints& Provider::Hints::newKeySet ()
    {
        myValue |= CRYPT_NEWKEYSET;
        return (*this);
    }

    Provider::Hints& Provider::Hints::machineKeySet ()
    {
        myValue |= CRYPT_MACHINE_KEYSET;
        return (*this);
    }

    Provider::Hints& Provider::Hints::deleteKeySet ()
    {
        myValue |= CRYPT_DELETEKEYSET;
        return (*this);
    }

    Provider::Hints& Provider::Hints::silent ()
    {
        myValue |= CRYPT_SILENT;
        return (*this);
    }

    Provider::Hints& Provider::Hints::defaultContainerOptional ()
    {
        myValue |= CRYPT_DEFAULT_CONTAINER_OPTIONAL;
        return (*this);
    }

    Provider::Hints::operator Value () const
    {
        return (myValue);
    }

} }
