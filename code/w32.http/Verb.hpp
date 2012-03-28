#ifndef _w32_http_Verb_hpp__
#define _w32_http_Verb_hpp__

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

    class Request;

    class Verb
    {
        /* nested types. */
    public:
        typedef ::HTTP_VERB Value;

        /* class methods. */
    public:
        static const Verb unparsed ();
        static const Verb unknown ();
        static const Verb invalid ();
        static const Verb options ();
        static const Verb get ();
        static const Verb head ();
        static const Verb post ();
        static const Verb put ();
        static const Verb delete_ ();
        static const Verb trace ();
        static const Verb connect ();
        static const Verb track ();
        static const Verb move ();
        static const Verb copy ();
        static const Verb propfind ();
        static const Verb proppatch ();
        static const Verb mkcol ();
        static const Verb lock ();
        static const Verb unlock ();
        static const Verb search ();

        static const Verb of ( const Request& request );

        /* data.*/
    public:
        Value myValue;

        /* construction. */
    private:
        Verb ( Value value );

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const Verb& rhs ) const;
        bool operator!= ( const Verb& rhs ) const;
    };

} }

#endif /* _w32_http_Verb_hpp__ */
