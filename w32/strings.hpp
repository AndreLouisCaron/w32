#ifndef _w32_strings_hpp__
#define _w32_strings_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/types.hpp>
#include <iterator>

namespace w32 {

    class W32_CORE_EXPORT strings
    {
        /* nested types. */
    public:
        typedef wchar_t char_type;
        typedef wchar_t* value_type;
        typedef dword size_type;
        class iterator;
        typedef Reference< wchar_t ** > Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        strings ();

        /* methods. */
    public:
        const wchar_t ** data () const;
        size_type size () const;
        iterator begin () const;
        iterator end () const;

        /* operators. */
    public:
        value_type operator[] ( size_type i ) const;
    };

    class W32_CORE_EXPORT strings::iterator :
        public std::iterator< std::forward_iterator_tag, std::size_t >
    {
    friend class strings;

        /* data. */
    private:
        const wchar_t ** myPosition;

        /* construction. */
    private:
        iterator ( const wchar_t ** position );

        /* operators. */
    public:
        const wchar_t * operator* () const;
        iterator& operator++ ();
        iterator operator++ ( int );
        bool operator== ( const iterator& other ) const;
        bool operator!= ( const iterator& other ) const;
    };

}

#endif /* _w32_strings_hpp__ */
