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
     */
    class Global
    {
        /* nested types. */
    public:
        typedef Reference< ::HGLOBAL > Handle;

        class Lock;

        /* class methods. */
    public:
        static Handle claim ( ::HGLOBAL object );
        static Handle proxy ( ::HGLOBAL object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Global ( size_t bytes );

        /* methods. */
    public:
        const Handle& handle () const;

            /*!
             * @brief Obtains the current size of the memory block.
             */
        std::size_t size () const;
    };

    class Global::Lock :
        private w32::NotCopyable
    {
        /* data. */
    private:
        void *const myLocation;

        /* construction. */
    public:
        explicit Lock ( Global& object );
        ~Lock ();

        /* methods. */
    public:
        void * location () const;
    };

} }

#endif /* _w32_mm_Global_hpp__ */
