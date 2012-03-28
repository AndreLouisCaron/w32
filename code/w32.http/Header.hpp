#ifndef _w32_http_Header_hpp__
#define _w32_http_Header_hpp__

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

namespace w32 { namespace http {

    class Header
    {
        /* nested types. */
    public:
        typedef ::HTTP_HEADER_ID Value;

        /* class data. */
    public:
        static const Header cachecontrol ();
        static const Header connection ();
        static const Header date ();
        static const Header keepalive ();
        static const Header pragma ();
        static const Header trailer ();
        static const Header transferencoding ();
        static const Header upgrade ();
        static const Header via ();
        static const Header warning ();

        static const Header allow ();
        static const Header contentlength ();
        static const Header contenttype ();
        static const Header contentencoding ();
        static const Header contentlanguage ();
        static const Header contentlocation ();
        static const Header contentmd5 ();
        static const Header contentrange ();
        static const Header expires ();
        static const Header lastmodified ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Header ( Value value );

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const Header& rhs ) const;
        bool operator!= ( const Header& rhs ) const;
    };

} }

#endif /* _w32_http_Header_hpp__ */
