#ifndef _w32_http_Group_hpp__
#define _w32_http_Group_hpp__

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
#include <w32/string.hpp>

namespace w32 { namespace http {

    class Queue;
    class Session;

    class Group
    {
        /* nested types. */
    public:
        typedef Reference< ::HTTP_URL_GROUP_ID > Handle;
        typedef ::HTTP_URL_CONTEXT Context;

        /* class methods. */
    public:
        static Handle claim ( ::HTTP_URL_GROUP_ID object );
        static Handle proxy ( ::HTTP_URL_GROUP_ID object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Group ( Session& session );

        /* methods. */
    public:
        const Handle& handle () const;

        void bind ( Queue& queue );

        void add ( const string& url, Context context );
        void add ( const string& url );
        void add ( const string& url, void * context );

        void del ( const string& url );
        void clear ();
    };

} }

#endif /* _w32_http_Group_hpp__ */