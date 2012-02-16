#ifndef _w32_mm_Heap_hpp__
#define _w32_mm_Heap_hpp__

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
#include <w32/Object.hpp>
#include <w32.mm/Allocator.hpp>

namespace w32 { namespace mm {

    /*!
     * @ingroup w32-mm
     */
    class Heap :
        public Object, public Allocator
    {
        /* nested types. */
    public:
        class Lock :
            private w32::NotCopyable
        {
            /* data. */
        private:
            const Heap& myHeap;

            /* construction. */
        public:
            explicit Lock ( const Heap& heap );
            ~Lock ();
        };

        class Walker;

        class Entry :
            private w32::NotCopyable
        {
        friend class Walker;

            /* nested types. */
        public:
            typedef ::PROCESS_HEAP_ENTRY Data;

            /* data. */
        private:
            Data myData;

            /* construction. */
        private:
            Entry ();

            /* methods. */
        public:
            Data& data ();
            const Data& data () const;

            bool busy () const;
            bool moveable () const;
        };

        class Walker :
            private w32::NotCopyable
        {
            /* data. */
        private:
            const Heap& myHeap;
            Entry myEntry;

            /* construction. */
        public:
            explicit Walker ( const Heap& heap );

            /* methods. */
        public:
            Entry& entry ();
            const Entry& entry () const;
            bool next ();
        };

        /* class methods. */
    public:
        static Heap process ();

        /* construction. */
    public:
        Heap ();
        explicit Heap ( const Handle& handle );

        /* methods. */
    public:
        void compact ();
        virtual dword flags ();

        /* overrides. */
    public:
        virtual void * acquire ( size_t amount );
        virtual void release ( void * location, size_t );
    };

} }

#endif /* _w32_mm_Heap_hpp__ */
