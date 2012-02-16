#ifndef _w32_net_Set_hpp__
#define _w32_net_Set_hpp__

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
#include <w32.net/integers.hpp>
#include <w32.net/Socket.hpp>

namespace w32 { namespace net {

    /*!
     * @ingroup w32-net
     * @brief List of sockets to pass to select().
     *
     * @note The underlying implementation is a fixed-capacity array of
     *   which we add or remove elements on demand (i.e. the size never
     *   changes, but we ensure
     */
    class Set :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::fd_set Data;
        typedef uint size_type;

    private:
        typedef ::SOCKET * iterator;
        typedef const ::SOCKET * const_iterator;

        /* data. */
    private:
        Data myData;

        /* construction . */
    public:
            /*!
             * @brief Builds an empty set.
             */
        Set ();

            /*!
             * @brief Clears the set.
             */
        ~Set ();

        /* class methods. */
    public:
            /*!
             * @brief Obtains the total number of sockets that can be
             *   simultaneously held in a file descriptor set.
             *
             * There is an upper bound on the number of file descriptors in this
             * set to ensure system-wide performance. Unfortunately, this limit
             * is decided for us.
             */
        static size_type capacity ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the native representation.
             *
             * @warning This function grants you write-access, effictively
             *   allowing you to violate this classe's invariants. Use it
             *   wisely.
             */
        Data& data ();

            /*!
             * @brief Obtains the native representation.
             */
        const Data& data () const;

            /*!
             * @brief Obtains the number of elements in the set.
             */
        size_type size () const;

            /*!
             * @brief Checks if there are no elements in the set.
             * @return True is the set contains 0 elements.
             *
             * @note This test is equal to <code>begin() == end()</code> or,
             *   equivalently, <code>size() == 0</code>.
             */
        bool empty () const;

            /*!
             * @brief Checks if the set is full.
             * @return True is the set contains @c capacity() elements.
             *
             * @note This test is equal to <code>size() == capacity()</code>.
             */
        bool full () const;

            /*!
             * @brief Removes all items in the set.
             */
        void clear ();

            /*!
             * @brief Adds an element to the set.
             *
             * Elements cannot be inserted twice; requests to insert a duplicate
             * element are simply ignored.
             *
             * @throw std::range_error The set has limited capacity and connot
             *   contain more than @c capacity() elements. To ensure this
             *   situation never occurs, check that @c full() returns @c false.
             */
        void add ( const Socket& socket );

            /*!
             * @brief Checks if an element was added to the set.
             * @return True if the element is a member of the set.
             */
        bool contains ( const Socket& socket ) const;

            /*!
             * @brief Removes an element from the set.
             *
             * Elements cannot be removed if they are not contained in the set;
             * requests to insert a duplicate element are simply ignored.
             */
        void remove ( const Socket& socket );

    private:
        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;
    };

} }

#endif /* _w32_net_Set_hpp__ */
