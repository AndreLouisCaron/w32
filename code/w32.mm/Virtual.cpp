// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mm/Virtual.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace mm {

    const Virtual::Access Virtual::Access::e ()
    {
        return (PAGE_EXECUTE);
    }

    const Virtual::Access Virtual::Access::r ()
    {
        return (PAGE_READONLY);
    }

    const Virtual::Access Virtual::Access::rw ()
    {
        return (PAGE_READWRITE);
    }

    const Virtual::Access Virtual::Access::re ()
    {
        return (PAGE_EXECUTE_READ);
    }

    const Virtual::Access Virtual::Access::rwe ()
    {
        return (PAGE_EXECUTE_READWRITE);
    }

    Virtual::Virtual ( const Access& access )
        : myAccess(access)
    {
    }

    void * Virtual::acquire ( size_t amount )
    {
        const ::LPVOID location = ::VirtualAlloc(
            0, amount, MEM_RESERVE|MEM_COMMIT, myAccess.value()
            );
        if ( location == 0 ) {
            UNCHECKED_WIN32C_ERROR(VirtualAlloc,::GetLastError());
        }
        return (location);
    }

    void Virtual::release ( const void * location, size_t )
    {
        const ::BOOL result = ::VirtualFree(
            const_cast<::LPVOID>(location), 0, MEM_RELEASE
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(VirtualFree,::GetLastError());
        }
    }

} }
