#ifndef _w32_mm_Global_hpp__
#define _w32_mm_Global_hpp__

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
#include <w32/Reference.hpp>
#include <w32/types.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     * @brief Legacy memory allocation protocol.
     *
     * You should not use this class unless a given interface requires you
     * to: modern mechanisms, which are also more convenient, exist.
     *
     * @see Heap
     * @see Local
     */
    class Global
    {
        /* nested types. */
    public:
        /*!
         * @brief Identifier for a memory block allocated on the global heap.
         */
        typedef Reference< ::HGLOBAL > Handle;

        class Lock;

        /* class methods. */
    public:
        /*!
         * @return A handle with a real deallocation function.
         */
        static Handle claim ( ::HGLOBAL object );

        /*!
         * @return A handle with a no-operation as a deallocation function.
         */
        static Handle proxy ( ::HGLOBAL object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @param bytes Size of the requeste memory block, in bytes.
         */
        Global ( size_t bytes );

        /* methods. */
    public:
        /*!
         * @return The local memory object's system handle.
         */
        const Handle& handle () const;

            /*!
             * @brief Obtains the current size of the memory block.
             */
        std::size_t size () const;
    };

    /*!
     * @brief Lock the requested memory block for access.
     */
    class Global::Lock :
        private w32::NotCopyable
    {
        /* data. */
    private:
        void *const myLocation;

        /* construction. */
    public:
        /*!
         * @brief Locks @a object, granting access the contents of the memory.
         */
        explicit Lock ( Global& object );

        /*!
         * @brief Releases the lock on the memory block.
         *
         * From this point on, you should not access the pointer returned by
         * @c location() any longer.
         */
        ~Lock ();

        /* methods. */
    public:
        /*!
         * @brief Obtains a pointer to the start of the memory block.
         */
        void * location () const;
    };

} }

#endif /* _w32_mm_Global_hpp__ */
