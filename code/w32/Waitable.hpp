#ifndef _w32_Waitable_hpp__
#define _w32_Waitable_hpp__

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
#include <w32/Object.hpp>
#include <w32/Timespan.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Kernel object that implements wait semantics.
     */
    class Waitable :
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

    class Waitable::Set :
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
        value_type operator[] ( size_type i ) const;

        Set& operator|= ( value_type value );
        Set& operator&= ( value_type value );
        bool operator& ( value_type value );

        Set& operator|= ( const Waitable& object );
        Set& operator&= ( const Waitable& object );
        bool operator& ( const Waitable& object );
    };

}

#endif /* _w32_Waitable_hpp__ */
