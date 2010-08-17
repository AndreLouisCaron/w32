#ifndef _w32_mm_Heap_hpp__
#define _w32_mm_Heap_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Object.hpp>
#include <w32/mm/Allocator.hpp>

namespace w32 { namespace mm {

    class W32_MM_EXPORT Heap :
        public Object, public Allocator
    {
        /* nested types. */
    public:
        class W32_MM_EXPORT Lock :
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

        class W32_MM_EXPORT Entry :
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

        class W32_MM_EXPORT Walker :
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
