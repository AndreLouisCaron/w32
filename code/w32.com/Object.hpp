#ifndef _com_Object_hpp__
#define _com_Object_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32.com/Allocator.hpp>
#include <w32.com/Guid.hpp>

namespace w32{ namespace com {

        /*!
         * @brief Implements the recurring parts of the IUnknown inteface.
         */
    class Object :
        public ::IUnknown, public NotCopyable
    {
        /* class operators. */
    public:
        inline void * operator new ( std::size_t size )
        {
            return (com::Allocator().acquire(size));
        }

        inline void * operator new
            ( std::size_t size, const std::nothrow_t& ) throw()
        {
            return (com::Allocator().acquire(size, std::nothrow));
        }

        inline void operator delete
            ( void * block, std::size_t ) throw()
        {
            return (com::Allocator().release(block));
        }

        /* data. */
    private:
        volatile ::LONG myReferenceCount;

        /* construction.*/
    public:
        Object ();
        virtual ~Object ();

        /* overrides. */
    public:
        ::ULONG __stdcall AddRef ();
        ::ULONG __stdcall Release ();
        ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            );

    protected:
        template<typename Interface>
        void * __stdcall query ( const Guid& guid )
        {
            if ( guid == guidof<Interface>() )
            {
                if ( void * object = dynamic_cast<Interface*>(this) ) {
                    AddRef(); return(object);
                }
            }
            return (0);
        }
    };

} }

#endif /* _w32_com_Object_hpp__ */
