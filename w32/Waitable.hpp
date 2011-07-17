#ifndef _w32_Waitable_hpp__
#define _w32_Waitable_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Object.hpp>
#include <w32/Timespan.hpp>

namespace w32 {

    class W32_CORE_EXPORT Waitable :
        public Object
    {
        /* nested types. */
    public:
        class Timeout {};
        class Set;

        /* class methods. */
    public:
        static dword any ( const Set& set );
        static dword any ( const Set& set, const w32::Timespan& timeout );
        static dword all ( const Set& set );
        static dword all ( const Set& set, const w32::Timespan& timeout );

        /* construction. */
    public:
        explicit Waitable ( const Handle& handle );

        /* methods. */
    public:
        void wait () const;
        bool wait ( const Timespan& timeout ) const;
        bool test () const;
    };

    class W32_CORE_EXPORT Waitable::Set :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::DWORD size_type;
        typedef ::HANDLE value_type;
        typedef value_type * iterator;
        typedef const value_type * const_iterator;

        /* data. */
    private:
        value_type myData[MAXIMUM_WAIT_OBJECTS];
        size_type mySize;

        /* construction. */
    public:
        Set ();

        /* methods. */
    public:
        size_type capacity () const;
        size_type size () const;
        const value_type * data () const;
        const_iterator begin () const { return (myData); }
        const_iterator end () const { return (begin()+size()); }
        bool empty () const { return (size() == 0); }
        bool full () const { return (size() == capacity()); }

    private:
        iterator begin () { return (myData); }
        iterator end () { return (begin()+size()); }

        /* operators. */
    public:
        Set& operator|= ( value_type value );
        Set& operator&= ( value_type value );
        bool operator& ( value_type value );
    };

}

#endif /* _w32_Waitable_hpp__ */
