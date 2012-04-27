#ifndef _idp_Buffer_hpp__
#define _idp_Buffer_hpp__

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

/*!
 * @file demo/ident/Buffer.hpp
 */

#include "__configure__.hpp"
#include <string>

namespace idp {

    class Buffer :
        private w32::NotCopyable
    {
        /* data. */
    private:
        w32::dword mySize;
        w32::byte* myData;

        // valid range.
        w32::dword myUbnd;
        w32::dword myLbnd;

        /* construction. */
    public:
        Buffer ( w32::dword capacity );

        ~Buffer ();

        /* methods. */
    public:
        // total buffer capacity.
        w32::dword capacity () const;

        // pointer to first available byte.
        void * data ();
        const void * data () const;

        // current buffer size.
        w32::dword size () const;

        // pointer to one-past-the-last, use for writing.
        void * next ();

        // size of unoccupied space, use for writing.
        w32::dword left () const;

        // advance lower bound (data has been consumed).
        void took ( w32::dword used );

        // advance upper bound (data was made available).
        void gave ( w32::dword size );

        // check if data ends at the end of the buffer.
        // note: this is _not_ equal to (size() == capacity()).
        bool full () const;

        // Check that size()==0.
        bool empty () const;

        // move all data to front.
        void pack ();

        // check if data starts at the beginning of the buffer.
        bool packed () const;

        // empty current buffer contents.
        void clear ();

        // empty contents, optionally erasing them for security/privacy.
        void clear ( bool erase );

        // erase confidential buffer contents for security/privacy..
        void erase ();

        void put ( const w32::byte * data, w32::dword size );

        void put ( const void * data, w32::dword size );

        void put ( const std::string& payload );
    };

}

#endif /* _idp_Buffer_hpp__ */
