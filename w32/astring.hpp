#ifndef _w32_astring_hpp__
#define _w32_astring_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Codepage.hpp>
#include <w32/types.hpp>
#include <iosfwd>
#include <string>

namespace w32 {

    class string;

    class W32_CORE_EXPORT astring
    {
        /* nested types. */
    public:
        typedef dword size_type;
        typedef char char_type;
        typedef char_type * iterator;
        typedef const char_type * const_iterator;

        class box;

        /* data. */
    private:
        dword mySize;
        char_type * myData;
        Codepage myEncoding;

        /* construction. */
    public:
        astring ();
        astring
            ( const char_type * other, Codepage encoding=Codepage::ansi() );
        astring
            ( const std::string& other );
        astring
            ( const std::string& other, Codepage encoding );
        astring
            ( const wchar_t * other, Codepage encoding=Codepage::ansi() );
        astring
            ( const std::wstring& other, Codepage encoding=Codepage::ansi() );
        astring ( const string& other, Codepage encoding=Codepage::ansi() );
        explicit astring ( const box& value );
        astring ( const astring& other );
        ~astring ();

        /* methods. */
    public:
        size_type size () const;
        size_type length () const;
        bool empty () const;

        const char_type * data () const;
        const char_type * c_str () const;
        char_type * data ();
        char_type * c_str ();

        const Codepage encoding () const;

        void swap ( astring& other );

        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;

        /* operators. */
    public:
        astring& operator= ( const astring& other );
        astring& operator= ( const char_type * other );
        astring& operator= ( const std::string& other );

        operator const std::string () const;
    };

    inline void swap ( astring& lhs, astring& rhs ) {
        lhs.swap(rhs);
    }

    W32_CORE_EXPORT std::ostream& operator<<
        ( std::ostream& out, const astring& value );

    inline astring::astring ( const std::string& other )
        : mySize(other.size()), myData(new char[mySize]),
          myEncoding(Codepage::ansi())
    {
        *std::copy(other.begin(), other.end(), begin()) = '\0';
    }

    inline astring::operator const std::string () const
    {
        return (std::string(data(), size()));
    }

    class W32_CORE_EXPORT astring::box
    {
        /* data. */
    private:
        dword mySize;
        char_type * myData;
        Codepage myEncoding;

        /* construction. */
    public:
        box ( char_type * data, Codepage encoding=Codepage::ansi() );
        box ( char_type * data, dword size );
        box (
            char_type * data, dword size, Codepage encoding=Codepage::ansi() );

        /* methods. */
    public:
        const dword size () const;
        char_type *const data () const;
        const Codepage encoding () const;
    };

}

#endif /* _w32_astring_hpp__ */
