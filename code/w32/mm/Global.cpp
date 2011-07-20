// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mm/Global.hpp>
#include <w32/Error.hpp>

namespace {

    ::HGLOBAL allocate ( ::SIZE_T bytes )
    {
        const ::HGLOBAL handle = ::GlobalAlloc(GMEM_ZEROINIT,bytes);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalAlloc, error);
        }
        return (handle);
    }

    void abandon ( ::HGLOBAL object ) {}
    void destroy ( ::HGLOBAL object )
    {
        const ::HGLOBAL result = ::GlobalFree(object);
        if ( result != 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalFree, error);
        }
    }

}

namespace w32 { namespace mm {

    Global::Handle Global::claim ( ::HGLOBAL object )
    {
        return (Handle(object, &::destroy));
    }

    Global::Handle Global::proxy ( ::HGLOBAL object )
    {
        return (Handle(object, &::abandon));
    }

    Global::Global ( size_t bytes )
        : myHandle(claim(::allocate(bytes)))
    {
    }

    const Global::Handle& Global::handle () const
    {
        return (myHandle);
    }

    Global::Lock::Lock ( Global& object )
        : myLocation(::GlobalLock(object.handle()))
    {
        if ( myLocation == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalLock, error);
        }
    }

    Global::Lock::~Lock ()
    {
        if ( ::GlobalUnlock(myLocation) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalUnlock, error);
        }
    }

    void * Global::Lock::location () const
    {
        return (myLocation);
    }

    std::size_t Global::size () const
    {
        const ::SIZE_T result = ::GlobalSize(handle());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GlobalSize, error);
        }
        return (result);
    }

} }
