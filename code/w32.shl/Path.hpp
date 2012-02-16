#ifndef _w32_shl_Path_hpp__
#define _w32_shl_Path_hpp__

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
#include <w32.com/Guid.hpp>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>

namespace w32 { namespace shl {

    class Path;

    Path manage ( ::LPITEMIDLIST path );

        /*!
         * @brief Singly-linked list of heterogenous component identifiers.
         *
         * Each namespace in the shell provides its own format for path
         * components. These components may contain arbitrary binary data.
         * Since a single path may contain components from several different
         * namespaces at the same time, you should treat this data as opaque,
         * safe for those you are supposed to have created.
         *
         * To ensure safe interaction between different namespaces, you should
         * double check all entries of shell paths to your extension and
         * diagnose errors as clearly as possible. For instance, if a provided
         * path is supposed to identify a direct child of a folder, then make
         * sure the number of components in the path is 1 and return
         * \c E_INVALIDARG if it doesn't.
         */
    class Path
    {
    friend Path manage ( ::LPITEMIDLIST path );

        /* nested types. */
    public:
        typedef ::UINT size_type;

            /*!
             * @brief Provides acess to individual components.
             */
        class iterator
        {
            /* data. */
        private:
            ::LPCITEMIDLIST myPosition;

            /* construction. */
        public:
            iterator ()
                 : myPosition(0)
            {}

            iterator ( ::LPCITEMIDLIST position )
                : myPosition(position)
            {}

            /* methods. */
        public:
            ::LPCITEMIDLIST position () const {
                return (myPosition);
            }

            /* operators. */
        public:
            const ::ITEMIDLIST& operator* () const {
                return (*myPosition);
            }

            ::LPCITEMIDLIST operator-> () const {
                return (myPosition);
            }

            void operator++ () {
                myPosition = ILNext(myPosition);
            }

            iterator operator++ ( int )
            {
                iterator previous(*this);
                ++(*this);
                return (previous);
            }

            bool operator== ( const iterator& other ) const {
                return (myPosition == other.myPosition);
            }

            bool operator!= ( const iterator& other ) const {
                return ( !((*this) == other) );
            }
        };

        typedef iterator const_iterator;

        /* data. */
    private:
        ::LPITEMIDLIST myBackend;

        /* static methods. */
    public:
#if 0
        static int compare ( const Path& lhs, const Path& rhs )
        {
            iterator l = lhs.begin();
            iterator r = lhs.begin();
            int result = 0;
            while ( (result == 0) && (l != lhs.end()) && (r != rhs.end()) ) {
                result = Component::compare(*l++,*r++);
            }
            return (result);
        }
#endif

            /*!
             * @brief Gains ownership of an existing path.
             */
        static Path box ( ::LPITEMIDLIST path ) {
            return (manage(path));
        }

        /* construction. */
    public:
        Path ();
        explicit Path ( ::LPCITEMIDLIST list );
        Path ( const Path& list );
        Path ( const string& path );

            /*!
             * @brief Concatenates two identifier lists.
             */
        Path ( ::LPCITEMIDLIST parent, ::LPCITEMIDLIST child );

            /*!
             * @brief Concatenates two identifier lists.
             */
        Path ( const Path& parent, const Path& child );

            /*!
             * @brief Allocates a component.
             */
        Path ( const void * data, const size_type size );

        ~Path ();

        /* methods. */
    public:
            /*!
             * @brief Obtains read-only access to the native representation.
             */
        ::LPCITEMIDLIST backend () const;

            /*!
             * @brief Requests manual management of the native representation.
             */
        ::LPITEMIDLIST release ();

            /*!
             * @brief Constant-time swap of the two paths.
             */
        void swap ( Path& other );

            /*!
             * @brief Obtains the total size of the path, in bytes.
             */
        size_type size () const;

        bool empty () const;

        void pop ();

            /*!
             * @brief Obtains the number of components in the path.
             */
        size_type components() const;

        iterator begin () const;
        iterator end () const;

        /* operators. */
    public:
        Path& operator= ( const Path& other );
        Path& operator= ( ::LPCITEMIDLIST other );
        operator bool () const;
        bool operator! () const;

        operator string () const;
    };

    bool operator== ( const Path& lhs, const Path& rhs );
    bool operator!= ( const Path& lhs, const Path& rhs );


        /*!
         * @brief Constant-time swap of the two paths.
         *
         * This function is provided for argument-based lookup.
         */
    inline void swap ( Path& lhs, Path& rhs ) {
        lhs.swap(rhs);
    }

        /*!
         * @brief Gains ownership of an existing path.
         */
    inline Path manage ( ::LPITEMIDLIST path )
    {
        Path result;
        result.myBackend = path;
        return (result);
    }

} }

#endif /*  _w32_shl_Path_hpp__ */
