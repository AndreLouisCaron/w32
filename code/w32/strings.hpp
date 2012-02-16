#ifndef _w32_strings_hpp__
#define _w32_strings_hpp__

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
#include <w32/Reference.hpp>
#include <w32/types.hpp>
#include <iterator>

namespace w32 {

    class strings
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

    class strings::iterator :
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
