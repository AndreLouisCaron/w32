#ifndef _w32_mt_List_hpp__
#define _w32_mt_List_hpp__

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
#include <iterator>

namespace w32 { namespace mt {

    class List :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SLIST_HEADER Data;
        typedef ::USHORT size_type;
        typedef ::SLIST_ENTRY Item;
        class iterator;
        class const_iterator;

        /* class data. */
    public:
        static const size_t alignment = MEMORY_ALLOCATION_ALIGNMENT;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        List ();
        ~List ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        size_type size () const;
        void push ( Item * item );
        Item * pop ();
        Item * clear ();
        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;
    };

    class List::iterator :
        public std::iterator< std::forward_iterator_tag, std::size_t >
    {
    friend class List;

        /* data. */
    private:
        List::Item * myPosition;

        /* construction. */
    private:
        explicit iterator ( List::Item * position );

        /* operators. */
    public:
        List::Item * operator* () const;
        iterator& operator++ ();
        iterator operator++ ( int );
        bool operator== ( const iterator& other ) const;
        bool operator!= ( const iterator& other ) const;
    };

    class List::const_iterator :
        public std::iterator< std::forward_iterator_tag, std::size_t >
    {
    friend class List;

        /* data. */
    private:
        const List::Item * myPosition;

        /* construction. */
    private:
        explicit const_iterator ( const List::Item * position );
        const_iterator ( const List::iterator& position );

        /* operators. */
    public:
        const List::Item * operator* () const;
        const_iterator& operator++ ();
        const_iterator operator++ ( int );
        bool operator== ( const const_iterator& other ) const;
        bool operator!= ( const const_iterator& other ) const;
    };

} }

#endif /* _w32_mt_List_hpp__ */
