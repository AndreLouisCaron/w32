#ifndef _w32_com_Allocator_hpp__
#define _w32_com_Allocator_hpp__

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

#include "__configure__.hpp"
#include <w32.com/Wrapper.hpp>
#include <new>

namespace w32{ namespace com {

    class Allocator :
        public Wrapper< ::IMalloc >
    {
        /* nested types. */
    public:
        typedef Wrapper< ::IMalloc >::Ptr Ptr;

        /* construction. */
    public:
        Allocator ();
        Allocator ( const Ptr& backend );

        /* methods. */
    public:
        bool acquired ( const void * block ) const;

        void * acquire ( long bytes );
        void * acquire ( long bytes, const std::nothrow_t& );
        void * reacquire ( const void * block, long bytes );

        template<typename T>
        T * acquire ( long count )
        {
            return (static_cast<T*>(acquire(count*sizeof(T))));
        }

        void release ( const void * block );

        void compact ();

        size_t size ( const void * block ) const;
    };

    inline void * operator new ( std::size_t size, Allocator& allocator )
    {
        return (allocator.acquire(size));
    }

    inline void * operator new (
        std::size_t size, const std::nothrow_t&, Allocator& allocator ) throw()
    {
        return (allocator.acquire(size, std::nothrow));
    }

    inline void operator delete
        ( void * block, std::size_t, Allocator& allocator ) throw()
    {
        return (allocator.release(block));
    }

    inline void * malloc ( std::size_t bytes )
    {
        void *const result = ::CoTaskMemAlloc(bytes);
        if ( result == 0 ) {
            throw (std::bad_alloc());
        }
        return (result);
    }

    inline void free ( void * block )
    {
        ::CoTaskMemFree(block);
    }

    wchar_t * strdup ( const wchar_t * source );

} }

#endif /* _com_Allocator_hpp__ */
