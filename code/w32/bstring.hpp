#ifndef _w32_bstring_hpp__
#define _w32_bstring_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <iosfwd>
#include <string>

namespace w32 {

    class string;

    class bstring
    {
        /* nested types. */
    public:
        typedef ::BSTR value_type;
        typedef ::HRESULT size_type;
        typedef ::OLECHAR char_type;
        typedef const char_type * const_pointer;
        typedef const_pointer const_iterator;

        class box;

        /* data. */
    private:
        value_type myValue;

        /* construction. */
    public:
        bstring ();
        bstring ( value_type contents );
        bstring ( const_pointer contents );
        bstring ( const_pointer contents, size_type size );
        bstring ( const string& other );
        bstring ( const bstring& other );
        explicit bstring ( const box& contents );
        ~bstring ();

        /* methods. */
    public:
        value_type value () const;
        const_pointer data () const;
        size_type size () const;
        size_type length () const;

        void swap ( bstring& rhs );
        bool empty () const;
        const_iterator begin () const;
        const_iterator end () const;

        /* operators. */
    public:
        bstring& operator= ( const bstring& other );
        bstring& operator= ( const_pointer contents );
        bstring& operator= ( const string& contents );
        bstring& operator= ( const std::wstring& contents );
        operator string() const;
        operator std::wstring() const;

        bool operator== ( const bstring& rhs ) const;
        bool operator!= ( const bstring& rhs ) const;
    };

    inline void swap ( bstring& lhs, bstring& rhs ) {
        lhs.swap(rhs);
    }

    std::wostream& operator<<
        ( std::wostream& out, const bstring& value );

    class bstring::box
    {
        /* data. */
    private:
        value_type myValue;

        /* construction. */
    public:
        explicit box ( value_type value );

        /* methods. */
    public:
        value_type value () const;
    };

}

#endif /* _w32_ole_bstring_hpp__ */
