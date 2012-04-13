#ifndef _w32_mm_Aligned_hpp__
#define _w32_mm_Aligned_hpp__

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
#include <w32/types.hpp>
#include <w32.mm/Allocator.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     * @brief Memory allocator that aligns pointers on a specific boundary.
     *
     * Some particular hardware operations mandate the use of memory aligned on
     * a specific boundary.  Typical requests are @c dword-aligned memory.
     * This is normally required when the hardware performs specific
     * optimizations on pointers.  One possible use of @c dword-aligned
     * (multiples of 4) pointers is to increase the total addressable amount of
     * memory (the lower 2 bits are always 0, so the address may be shifted,
     * resulting in 4 times the amount of addressable memory).
     *
     * @note Do not use this allocation scheme unless a particular API requests
     *  it.
     */
    class Aligned :
        public Allocator
    {
        /* data. */
    private:
        size_t myAlignment;

        /* class methods. */
    public:
        /*!
         * @brief Validates that the system supports the requested alignment.
         * @param alignment Boundary on which allocation should be aligned.
         * @return @c true if @a alignment is a non-zero power of two.
         */
        static bool supports ( size_t alignment );

        /* construction. */
    public:
        /*!
         * @brief Builds an allocator aligning on a multiple of @a alignment.
         * @see supports()
         */
        Aligned ( size_t alignment );

        /* methods. */
    public:
        size_t alignment () const {
            return (myAlignment);
        }

        /* overrides. */
    public:
        virtual void * acquire ( size_t amount );
        virtual void release ( void * start, size_t );
    };

} }

#endif /* _w32_mm_Aligned_hpp__ */
