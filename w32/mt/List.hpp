#ifndef _w32_mt_List_hpp__
#define _w32_mt_List_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <iterator>

namespace w32 { namespace mt {

    class W32_MT_EXPORT List :
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

    class W32_MT_EXPORT List::iterator :
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

    class W32_MT_EXPORT List::const_iterator :
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
