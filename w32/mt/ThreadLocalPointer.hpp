#ifndef _w32_mt_ThreadLocalPointer_hpp__
#define _w32_mt_ThreadLocalPointer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace mt {

    class ThreadLocalPointer :
        private NotCopyable
    {
        /* nested types. */
    public:
        class Handle :
            private w32::NotCopyable
        {
            /* nested types. */
        public:
            typedef dword Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        public:
            explicit Handle ( Value value );
            ~Handle ();

            /* methods. */
        public:
            bool bad () const;
            bool ok () const;
            Value value () const;
        };

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        ThreadLocalPointer ();

        /* methods. */
    public:
        const Handle& handle () const;
        void * get () const;
        void set ( void * value );

        /* operators. */
    public:
        ThreadLocalPointer& operator= ( void * value );
        operator void* () const;
    };

} }

#endif /* _w32_mt_ThreadLocalPointer_hpp__ */
