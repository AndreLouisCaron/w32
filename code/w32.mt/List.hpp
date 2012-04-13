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

    /*!
     * @brief Built-in thread-safe singly-linked list.
     *
     * The MSDN documentation states: An interlocked singly linked list (SList)
     * eases the task of insertion and deletion from a linked list.  SLists are
     * implemented using a nonblocking algorithm to provide atomic
     * synchronization, increase system performance, and avoid problems such as
     * priority inversion and lock convoys.
     *
     * However, the interface to this syncrhonization tool really sucks:
     * @li although it is called a singly-linked list, it has a stack's
     *  interface;
     * @li @c size() does not actually return the number of items in the list;
     * @li genericity through @c List::Item is restrictive;
     * @li special care must be taken in memory allocation;
     * @li there is no support for automatic cleanup;
     * @li iterating over the items in the list is totally unsafe.
     *
     * If you're considering using this class to implement a producer-consumer
     * scheme in, you might want to at lock-free queue implementations.
     *
     * @see http://www.drdobbs.com/high-performance-computing/208801974
     * @see http://www.drdobbs.com/high-performance-computing/210604448
     */
    class List :
        private NotCopyable
    {
        /* nested types. */
    public:
        /*!
         * @brief List header.
         */
        typedef ::SLIST_HEADER Data;

        /*!
         * @brief Integer type representing the size of a list.
         *
         * Although this type is a 16-bit unsigned integer, more than 2^16
         * items may be stored in the list: @c size() simply returns the number
         * of elements modulo 65535.
         */
        typedef ::USHORT size_type;

        /*!
         * @brief List item header.
         *
         * There are basically two ways to use this structure.  Either define
         * a structure that has an @c Item as its first member:
         * @code
         *  struct MyItem
         *  {
         *      w32::mt::List::Item header;
         *      // ...
         *  };
         * @endcode
         * or inherit from this class:
         * @code
         *  struct MyItem :
         *      w32::mt::List::Item
         *  {
         *      // ...
         *  };
         * @endcode
         * The 2nd scenario is usually cleaner than the 1st because it doesn't
         * require a @c reinterpret_cast when using @c push() and @c pop().
         * Only a @c static_cast is required with @c pop().
         *
         * @warning No matter which scenario you select, the @c struct may
         * @e never* contain virtual functions, because a pointer to the
         * virtual table is stored at the beginning of the object.
         */
        typedef ::SLIST_ENTRY Item;

        class iterator;
        class const_iterator;

        /* class data. */
    public:
        /*!
         * @see w32::mm::Alignment
         */
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
        /*!
         * @brief Obtain the list header.
         */
        Data& data ();

        /*!
         * @brief Obtain the list header.
         */
        const Data& data () const;

        /*!
         * @brief Count the number of items in the list.
         * @return The number of elements in the list, modulus 65535.
         */
        size_type size () const;

        /*!
         * @brief Adds @a item to the front of the list.
         * @param item Item to add to the list.  This item must be allocated to
         *  an @c alignment byte boundary.
         */
        void push ( Item * item );

        /*!
         * @brief Removes the first item in the list.
         */
        Item * pop ();

        /*!
         * @brief Removes all of the items in the list.
         * @return A pointer to the first item in the list.
         */
        Item * clear ();

        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;
    };

    /*!
     * @brief Iterator to the (mutable) list contents.
     * @warning Although the @c push(), @c pop() and @c size() functions are
     *  atomic, @c begin() and @c end() are not.  Moreover, the state of the
     *  list is not guaranteed to stay the same during iteration.  If any
     *  iteration is performed, @e all forms of access must be synchronized
     *  using a @c w32::mt::Mutex or other locking mechanism external to the
     *  list itself.
     */
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

    /*!
     * @brief Iterator to the (immutable) list contents.
     * @warning Although the @c push(), @c pop() and @c size() functions are
     *  atomic, @c begin() and @c end() are not.  Moreover, the state of the
     *  list is not guaranteed to stay the same during iteration.  If any
     *  iteration is performed, @e all forms of access must be synchronized
     *  using a @c w32::mt::Mutex or other locking mechanism external to the
     *  list itself.
     */
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
