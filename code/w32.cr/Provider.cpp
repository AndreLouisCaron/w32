// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.cr/Provider.hpp>
#include <w32/Error.hpp>
#include <w32/astring.hpp>
#include <w32/string.hpp>
#include <string>

namespace {

    ::HCRYPTPROV acquire ( ::DWORD type )
    {
        ::HCRYPTPROV handle = 0;
        const ::BOOL result = ::CryptAcquireContext
            (&handle, 0, 0, type, 0);
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
        : myHandle(claim(::acquire(type)))
    {
    }

    const Provider::Handle& Provider::handle () const
    {
        return (myHandle);
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

} }
