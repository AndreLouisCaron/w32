#ifndef _w32_mstring_hpp__
#define _w32_mstring_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
#include <iterator>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Multiple strings delimited by null characeters.
     */
    class mstring
    {
        /* nested types. */
    public:
        class iterator;

        /* data. */
    private:
        string myData;

        /* construction. */
    public:
        explicit mstring ( const string::box& data );
        explicit mstring ( const string& data );
        explicit mstring ( const wchar_t * data );
        mstring ( const mstring& rhs );

        /* methods. */
    public:
        iterator begin () const;
        iterator end () const;
        void swap ( mstring& rhs );

        /* operators. */
    public:
        mstring& operator= ( const mstring& rhs );
    };

    void swap ( mstring& lhs, mstring& rhs );

    class mstring::iterator :
        public std::iterator< std::forward_iterator_tag, std::size_t >
    {
    friend class mstring;

        /* data. */
    private:
        const wchar_t * myPosition;

        /* construction. */
    private:
        explicit iterator ( const wchar_t * position );

        /* operators. */
    public:
        const wchar_t * operator* () const;
        iterator& operator++ ();
        iterator operator++ ( int );
        bool operator== ( const iterator& other ) const;
        bool operator!= ( const iterator& other ) const;
    };

}

#endif /* _w32_mstring_hpp__ */
