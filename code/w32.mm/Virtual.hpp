#ifndef _w32_mm_Virtual_hpp__
#define _w32_mm_Virtual_hpp__

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
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>
#include <w32.mm/Allocator.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     * @brief Lowest-level memory allocation scheme.
     *
     * Strictly speaking, virual memory allocation is a technique used to
     * give an application program the impression that it has contiguous
     * working memory (called the address space) while in fact it may be
     * physically fragmented and may even overflow on to disk storage.
     *
     * This low-level facility is used to allocate very large amounts of
     * memory (the smallest granularity is a @e page of memory), or to
     * have fine grained control over access to the allocated memory.
     *
     * @note Do not be fooled into using other memory allocation shemes
     *   to avoid having your memory overflow to disk storage. This
     *   mechanism applies to all memory in the operating system: all
     *   other allocation schemes, including @c malloc() eventually
     *   resort to allocating virtual memory (albeit through other
     *   system memory allocators).
     *
     * @warning For conveniance, this class implements the @c Allocator
     *   interface. However, this requires returning a non-@c const pointer
     *   even when allocating read-only memory blocks. Write operations on
     *   read-only blocks causes access violations.
     *
     * @see w32::dbg::StructuredException
     */
    class Virtual :
        public Allocator
    {
        /* nested types. */
    public:
            /*!
             * @brief Memory access enumeration.
             *
             * Memory access should be controlled, primarily for security
             * concerns. Access is declined in 3 flavors: read(r), write(w) and
             * execute(e). You should normally deny code execution in the memory
             * block unless you require runtime code generation (unlikely, but
             * possible) or writing your own executable loader. Furthermore,
             * write access is usually denied when defining read-only locations.
             */
        class Access
        {
            /* class data. */
        public:
                /*!
                 * @brief Allow to execute code.
                 */
            static const Access e ();

                /*!
                 * @brief Allow to read.
                 */
            static const Access r ();

                /*!
                 * @brief Allow to read & write.
                 */
            static const Access rw ();

                /*!
                 * @brief Allow to read & execute code.
                 */
            static const Access re ();

                /*!
                 * @brief Allow to read & write, as well as to execute code.
                 */
            static const Access rwe ();

            /* nested types. */
        public:
                /*!
                 * @brief Native representation of enumerated values.
                 */
            typedef dword Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            Access ( Value value )
                : myValue(value)
            {}

            /* methods. */
        public:
                /*!
                 * @brief Obtain the value's native representation.
                 */
            Value value () const {
                return (myValue);
            }
        };

        /* data. */
    private:
        Access myAccess;

        /* construction. */
    public:
            /*!
             * @brief Builds a virtual memory allocator 
             */
        Virtual ( const Access& access );

        /* overrides. */
    public:
        virtual void * acquire ( size_t amount );
        virtual void release ( const void * start, size_t );
    };

} }

#endif /* _w32_mm_Virtual_hpp__ */
