#ifndef _w32_shl_Path_hpp__
#define _w32_shl_Path_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.com/Guid.hpp>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iterator>

namespace w32 { namespace shl {

    class Path;

    Path manage ( ::ITEMIDLIST * path );

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
    friend Path manage ( ::ITEMIDLIST * path );

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
            const ::ITEMIDLIST * myPosition;

            /* construction. */
        public:
            iterator ()
                 : myPosition(0)
            {}

            iterator ( const ::ITEMIDLIST * position )
                : myPosition(position)
            {}

            /* methods. */
        public:
            const ::ITEMIDLIST * position () const {
                return (myPosition);
            }

            /* operators. */
        public:
            const ::ITEMIDLIST& operator* () const {
                return (*myPosition);
            }

            const ::ITEMIDLIST* operator-> () const {
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
        ::ITEMIDLIST * myBackend;

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
        static Path box ( ::ITEMIDLIST * path ) {
            return (manage(path));
        }

        /* construction. */
    public:
        Path ();
        explicit Path ( const ::ITEMIDLIST * list );
        Path ( const Path& list );
        Path ( const string& path );

            /*!
             * @brief Concatenates two identifier lists.
             */
        Path ( const ::ITEMIDLIST * parent, const ::ITEMIDLIST * child );

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
        const ::ITEMIDLIST * backend () const;

            /*!
             * @brief Requests manual management of the native representation.
             */
        ::ITEMIDLIST * release ();

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
        Path& operator= ( const ::ITEMIDLIST * other );
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
    inline Path manage ( ::ITEMIDLIST * path )
    {
        Path result;
        result.myBackend = path;
        return (result);
    }

} }

#endif /*  _w32_shl_Path_hpp__ */
