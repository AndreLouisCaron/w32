#ifndef _w32_mm_Shared_hpp__
#define _w32_mm_Shared_hpp__

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
#include <w32/Object.hpp>
#include <w32/types.hpp>
#include <w32/string.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     * @brief Named chunk of memory that can subsequently be mapped onto
     *   other processes' address spaces.
     */
    class Shared :
        virtual public Object
    {
        /* data. */
    private:
        void *const myLocation;

        /* construction. */
    protected:
        explicit Shared ( void * location );

    public:
        explicit Shared ( const string& name );

            /*!
             * @brief Creates a named shared memory block and maps it to the
             *    process' address space.
             *
             * @param name Name of the shared memory object. This must be
             *    communicated to another process for it to map the same memory
             *    into it's address space. This name is case sensitive.
             * @param amount Total number of bytes of memory to allocate.
             *
             * @note The other process(es) that will map the same memory will
             *    obviously inherit a chunk of exactly the same size.
             */
        Shared ( const string& name, size_t amount );

        /* methods. */
    public:
            /*!
             * @brief Obtains the address of the first byte of allocated memory.
             */
        void * location ();

            /*!
             * @brief Obtains the address of the first byte of allocated memory.
             */
        const void * location () const;
    };

} }

#endif /* _w32_mm_Shared_hpp__ */
