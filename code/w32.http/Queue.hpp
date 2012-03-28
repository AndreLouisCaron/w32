#ifndef _w32_http_Queue_hpp__
#define _w32_http_Queue_hpp__

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
#include <w32/types.hpp>
#include <w32.http/Chunk.hpp>
#include <w32.http/Library.hpp>
#include <w32.http/Request.hpp>
#include <w32.http/Response.hpp>

namespace w32 { namespace http {

    class Queue
    {
        /* nested types. */
    public:
        typedef Reference< ::HANDLE > Handle;

        static Handle claim ( ::HANDLE object );
        static Handle proxy ( ::HANDLE object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Queue ( const Library& library );

        /* methods. */
    public:
        const Handle& handle () const;

        void shutdown ();

        void get ( Request& request );
        bool get ( Request::Id id, Request& request );

        void put ( const Request& request, Response& response );
        void put ( const Request::Id& request, Response& response );

        void cache ( const string& url, Chunk& chunk );
        void cache ( const string& url, Chunk& chunk, ulong seconds );
        void clear ( const string& url, bool recursive=false );
    };

} }

#endif /* _w32_http_Queue_hpp__ */
