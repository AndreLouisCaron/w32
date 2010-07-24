// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mm/Heap.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE get ()
    {
        const ::HANDLE handle = ::GetProcessHeap();
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetProcessHeap,::GetLastError());
        }
        return (handle);
    }

    ::HANDLE create ( ::SIZE_T initial, ::SIZE_T maximum )
    {
        const ::HANDLE handle = ::HeapCreate(0, initial, maximum);
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapCreate,::GetLastError());
        }
        return (handle);
    }

    void destroy ( ::HANDLE object )
    {
        const ::BOOL result = ::HeapDestroy(object);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(HeapDestroy, error);
        }
    }

}

namespace w32 { namespace mm {

    Heap Heap::process ()
    {
        return (Heap(proxy(::get())));
    }

    Heap::Heap ()
        : Object(Handle(::create(0,0), &::destroy))
    {
    }

    Heap::Heap ( const Handle& handle )
        : Object(handle)
    {
    }

    dword Heap::flags ()
    {
        return (0);
    }

    void Heap::compact ()
    {
        if ( ::HeapCompact(handle(), 0) == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapCompact,::GetLastError());
        }
    }

    void * Heap::acquire ( size_t amount )
    {
        const ::LPVOID location = ::HeapAlloc(
            handle(), flags(), amount
            );
        if ( location == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapAlloc,::GetLastError());
        }
        return (location);
    }

    void Heap::release ( void * location, size_t )
    {
        if ( ::HeapFree(handle(), 0, location) == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapFree,::GetLastError());
        }
    }

    Heap::Lock::Lock ( const Heap& heap )
        : myHeap(heap)
    {
        if ( ::HeapLock(myHeap.handle()) == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapLock,::GetLastError());
        }
    }

    Heap::Lock::~Lock ()
    {
        if ( ::HeapUnlock(myHeap.handle()) == 0 ) {
            UNCHECKED_WIN32C_ERROR(HeapUnlock,::GetLastError());
        }
    }

    Heap::Walker::Walker ( const Heap& heap )
        : myHeap(heap)
    {
        const ::BOOL result = ::HeapWalk(
            myHeap.handle(), &myEntry.myData
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(HeapWalk, error);
        }
    }

    Heap::Entry::Entry ()
    {
            // Clear out the memory, just to make sure.
        ::ZeroMemory(&myData, sizeof(myData));
    }

    bool Heap::Entry::busy () const
    {
        return ((myData.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0);
    }

    bool Heap::Entry::moveable () const
    {
        return ((myData.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0);
    }

    Heap::Entry& Heap::Walker::entry ()
    {
        return (myEntry);
    }

    const Heap::Entry& Heap::Walker::entry () const
    {
        return (myEntry);
    }

    bool Heap::Walker::next ()
    {
        const ::BOOL result = ::HeapWalk(
            myHeap.handle(), &myEntry.myData
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_ITEMS ) {
                return (true);
            }
            UNCHECKED_WIN32C_ERROR(HeapWalk, error);
        }
        return (true);
    }

} }
