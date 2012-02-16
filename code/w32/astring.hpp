#ifndef _w32_astring_hpp__
#define _w32_astring_hpp__

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
#include <w32/Codepage.hpp>
#include <w32/types.hpp>
#include <iosfwd>
#include <string>

namespace w32 {

    class string;

    /*!
     * @ingroup w32
     * @brief ANSI string.
     * @see Codepage
     */
    class astring
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

    std::ostream& operator<<
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

    class astring::box
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
