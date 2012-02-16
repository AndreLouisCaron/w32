#ifndef _w32_bstring_hpp__
#define _w32_bstring_hpp__

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
#include <w32/types.hpp>
#include <iosfwd>
#include <string>

namespace w32 {

    class string;

    /*!
     * @ingroup w32
     * @brief Visual Basic string.
     */
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
