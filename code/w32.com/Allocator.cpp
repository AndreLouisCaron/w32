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
