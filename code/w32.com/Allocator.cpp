// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.com/Allocator.hpp>
#include <w32.com/Result.hpp>
#include <w32.com/Error.hpp>
#include <exception>

namespace {

    ::IMalloc * fetch ()
    {
        ::IMalloc * value = 0;
        const w32::com::Result result(::CoGetMalloc(1, &value));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(<unnammed>, CoGetMalloc, result);
        }
        return (value);
    }

}

namespace w32 { namespace com {

    Allocator::Allocator ()
        : Wrapper< ::IMalloc >( ::fetch() )
    {
    }

    Allocator::Allocator ( const Ptr& backend )
        : Wrapper< ::IMalloc >(backend)
    {
    }

    bool Allocator::acquired ( const void * block ) const
    {
        return (backend().DidAlloc(const_cast<void*>(block)) != 0);
    }

    void * Allocator::acquire ( long bytes )
    {
        void *const result = acquire(bytes, std::nothrow);
        if ( result == 0 ) {
            throw (std::bad_alloc());
        }
        return (result);
    }

    void * Allocator::acquire ( long bytes, const std::nothrow_t& )
    {
        return (backend().Alloc(bytes));
    }

    void * Allocator::reacquire ( const void * block, long bytes )
    {
        void *const result = backend().Realloc
            (const_cast<void*>(block), bytes);
        if ( result == 0 ) {
            throw (std::bad_alloc());
        }
        return (result);
    }

    void Allocator::release ( const void * block )
    {
        backend().Free(const_cast<void*>(block));
    }

    void Allocator::compact ()
    {
        backend().HeapMinimize();
    }

    size_t Allocator::size ( const void * block ) const
    {
        return (backend().GetSize(const_cast<void*>(block)));
    }

    wchar_t * strdup ( const wchar_t * source )
    {
        const size_t length = ::wcslen(source);
        wchar_t *const clone =
            (wchar_t*)com::malloc(length*sizeof(wchar_t));
        return (::wcscpy(clone, source));
    }

} }
