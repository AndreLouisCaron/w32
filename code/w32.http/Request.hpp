#ifndef _w32_http_Request_hpp__
#define _w32_http_Request_hpp__

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
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32/Reference.hpp>

namespace w32 { namespace http {

    class Verb;

    class Request
    {
        /* nested types. */
    public:
        typedef ::HTTP_REQUEST_V2 Data;
        typedef ::HTTP_REQUEST_ID Id;

        class Header;

        /* class methods. */
    public:
        static const Id null ();

        /* data. */
    private:
        size_t mySize;
        Reference< void* > myData;

        /* construction. */
    public:
        Request ( size_t size );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        const size_t size () const;

        void clear ();

        const Id id () const;
        const Verb verb () const;
        const string resource () const;
    };

    class Request::Header
    {
        /* nested types. */
    public:
        typedef ::HTTP_HEADER_ID Value;

        /* class data. */
    public:
        static const Header accept ();
        static const Header acceptcharset ();
        static const Header acceptencoding ();
        static const Header acceptlanguage ();
        static const Header authorization ();
        static const Header cookie ();
        static const Header expect ();
        static const Header from ();
        static const Header host ();
        static const Header ifmatch ();
        static const Header ifmodifiedsince ();
        static const Header maxforwards ();
        static const Header proxyauthorization ();
        static const Header referer ();
        static const Header range ();
        static const Header te ();
        static const Header translate ();
        static const Header useragent ();
        static const Header requestmaximum ();

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

#endif /* _w32_http_Request_hpp__ */
