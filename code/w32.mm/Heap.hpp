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
     * @brief Private memory allocator.
     *
     * Using a private heap for allocation memory in fixed-size blocks can
     * reduce memory fragmentation and increase allocation speed considerably.
     * Moreover, if always used by a single thread, synchronization can be
     * disabled, further increasing speed.
     *
     * Upon destruction, the heap reclaims all memory allocated by the heap,
     * returning the virtual memory pages to the system. This is the key to
     * reducing memory fragmentation.
     */
    class Heap :
        public Object, public Allocator
    {
        /* nested types. */
    public:
        /*!
         * @brief Mutual exclusion lock for the heap.
         *
         * Acquires the critical section associated with the heap, preventing
         * other threads from allocating memory.
         *
         * This mechanism is useful when walking the heap, because it prevents
         * other threads from modifying the heap while it its entries are being
         * enumerated.
         *
         * @warning Results are undefined for locking attempts on heaps for
         *  which serialization was disabled (never applies to the default
         *  heap).
         */
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
            /*!
             * @brief Native representation.
             */
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

        /*!
         * @brief Enumerator for heap entries.
         *
         * @note You should lock the heap before you enumerate its entries.
         */
        class Walker :
            private w32::NotCopyable
        {
            /* data. */
        private:
            const Heap& myHeap;
            Entry myEntry;

            /* construction. */
        public:
            /*!
             * @brief Create an enumerator for memory blocks in @a heap.
             */
            explicit Walker ( const Heap& heap );

            /* methods. */
        public:
            /*!
             * @brief Access the current heap entry.
             */
            Entry& entry ();

            /*!
             * @brief Access the current heap entry.
             */
            const Entry& entry () const;

            /*!
             * @brief Walks up to the next heap entry.
             * @return If finished, @c false.
             *
             * The first result is obtained be the constructor, use it before
             * calling this method.  It is best to use a do-while loop to
             * enumerate heap entries.
             */
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
        /*!
         * @brief Merge adjacent freed blocks of memory, reduce fragmentation.
         *
         * @note The heap is automatically compacted when memory is freed.
         *  This function is only useful if you disable memory compacting for
         *  the entire system (see Debugging Tools for Windows).
         */
        void compact ();

        /*!
         * @return Flags set at heap creation (always 0 for the default heap).
         */
        virtual dword flags ();

        /* overrides. */
    public:
        virtual void * acquire ( size_t amount );
        virtual void release ( void * location, size_t );
    };

} }

#endif /* _w32_mm_Heap_hpp__ */
