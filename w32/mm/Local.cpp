// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mm/Local.hpp>
#include <w32/Error.hpp>

namespace {

    ::HGLOBAL allocate ( ::SIZE_T bytes )
    {
        const ::HGLOBAL handle = ::LocalAlloc(LMEM_ZEROINIT,bytes);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalAlloc, error);
        }
        return (handle);
    }

    void abandon ( ::HGLOBAL object ) {}
    void destroy ( ::HGLOBAL object )
    {
        const ::HGLOBAL result = ::LocalFree(object);
        if ( result != 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalFree, error);
        }
    }

}

namespace w32 { namespace mm {

    Local::Handle Local::claim ( ::HGLOBAL object )
    {
        return (Handle(object, &::destroy));
    }

    Local::Handle Local::proxy ( ::HGLOBAL object )
    {
        return (Handle(object, &::abandon));
    }

    Local::Local ( size_t bytes )
        : myHandle(claim(::allocate(bytes)))
    {
    }

    const Local::Handle& Local::handle () const
    {
        return (myHandle);
    }

    Local::Lock::Lock ( Local& object )
        : myLocation(::LocalLock(object.handle()))
    {
        if ( myLocation == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalLock, error);
        }
    }

    Local::Lock::~Lock ()
    {
        if ( ::LocalUnlock(myLocation) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalUnlock, error);
        }
    }

    void * Local::Lock::location () const
    {
        return (myLocation);
    }

    std::size_t Local::size () const
    {
        const ::SIZE_T result = ::LocalSize(handle());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LocalSize, error);
        }
        return (result);
    }

} }
