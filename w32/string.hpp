#ifndef _w32_string_hpp__
#define _w32_string_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Codepage.hpp>
#include <w32/types.hpp>
#include <iostream>
#include <string>

namespace w32 {

    class astring;
    class bstring;

    class W32_CORE_EXPORT string
    {
        /* nested types. */
    public:
        typedef dword size_type;
        typedef wchar_t char_type;
        typedef char_type * pointer;
        typedef const char_type * const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

        class box;

        /* class data. */
    public:
        static const size_type npos;

        /* data. */
    private:
        size_type mySize;
        pointer myData;

        /* construction. */
    public:
        string ();
        string ( const char * other, Codepage encoding=Codepage::ansi() );
        string ( const char * other, size_type size,
            Codepage encoding=Codepage::ansi() );
        string ( const astring& other );
        string ( const std::string& other,
            Codepage encoding=Codepage::ansi() );
        string ( const_pointer other );
        string ( const_pointer other, size_type size );
        string ( const bstring& other );
        string ( const std::wstring& other );

        string ( const dword size, char_type filler = L'\0' );

        explicit string ( const box& value );
        string ( const string& other );
        ~string ();

        /* methods. */
    public:
        size_type size () const;
        size_type length () const;
        bool empty () const;

        pointer data ();
        const_pointer data () const;
        pointer c_str ();
        const_pointer c_str () const;

        void swap ( string& other );

        void erase ( iterator begin, iterator end );
        void resize ( size_type length, char_type filler = L'\0' );

        string substr ( size_type offset, size_type length = npos ) const;

        void clear ();

        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;

        /* operators. */
    public:
        string& operator= ( const string& other );
        string& operator= ( const_pointer other );
        string& operator= ( const std::wstring& other );

        char_type& operator[] ( size_type i );
        char_type operator[] ( size_type i ) const;

        operator const std::wstring () const;

        string& operator+= ( const string& rhs );
        string operator+ ( const string& rhs ) const;

        string& operator+= ( wchar_t rhs );
        string operator+ ( wchar_t rhs ) const;
    };

    W32_CORE_EXPORT bool operator==
        ( const string& lhs, const string& rhs );
    W32_CORE_EXPORT bool operator!=
        ( const string& lhs, const string& rhs );

    W32_CORE_EXPORT string operator+
        ( const wchar_t * lhs, const string& rhs );

    inline void swap ( string& lhs, string& rhs ) {
        lhs.swap(rhs);
    }

    inline string::char_type& string::operator[] ( size_type i )
    {
        return (myData[i]);
    }

    inline string::char_type string::operator[] ( size_type i ) const
    {
        return (myData[i]);
    }

    inline string::string ( const std::wstring& other )
        : mySize(other.size()), myData(new wchar_t[mySize])
    {
        *std::copy(other.begin(), other.end(), begin()) = L'\0';
    }

    inline string::operator const std::wstring () const
    {
        return (std::wstring(begin(), end()));
    }

    W32_CORE_EXPORT std::wostream& operator<<
        ( std::wostream& out, const string& value );

    class W32_CORE_EXPORT string::box
    {
        /* data. */
    private:
        size_type mySize;
        pointer myData;

        /* construction. */
    public:
        explicit box ( pointer data );
        box ( pointer data, size_type size );

        /* methods. */
    public:
        size_type size () const;
        pointer data () const;
    };

    inline std::wistream& getline
        ( std::wistream& in, string& value, const wchar_t delimiter )
    {
        typedef std::wistream::traits_type traits;
        std::wios::iostate state = std::wios::goodbit;
        bool changed = false;
        const std::wistream::sentry ok(in,true);
        if ( in )
        {
            value.clear();
            const int stop = traits::to_int_type(delimiter);
            for ( traits::int_type meta = in.rdbuf()->sgetc();
                ; meta = in.rdbuf()->snextc() )
            {
                if ( traits::eq_int_type(traits::eof(),meta) ) {
                    state |= std::wios::eofbit; break;
                }
                else if ( traits::eq_int_type(meta, stop) ) {
                    changed = true; in.rdbuf()->sbumpc(); break;
                }
                else {
                    value += traits::to_char_type(meta); changed = true;
                }
            }
            if ( !changed ) {
                state |= std::wios::failbit;
            }
            in.setstate(state);
        }
        return (in);
    }

}

#endif /* _w32_string_hpp__ */
