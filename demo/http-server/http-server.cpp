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
 * @file demo/http-server/http-server.cpp
 * @brief Simple HTTP server based on @c w32::http services.
 */

#include <w32.hpp>
#include <w32.http.hpp>

#include <w32/app/console-program.hpp>

namespace {

    const w32::http::Verb GET
        = w32::http::Verb::get();

    const w32::http::Verb POST
        = w32::http::Verb::post();

    const w32::http::Header ContentType
        = w32::http::Header::contenttype();

    int run ( int argc, wchar_t ** argv )
    {
        // Runtime library "constructors".
        const w32::http::Library::Version version
            = w32::http::Library::Version::_2();
        const w32::http::Library library(version);
        
            // Allocate a request queue.
        std::cout<< "(( creating queue. ))" << std::endl;
        w32::http::Queue queue(library);
        
            // Define a couple URLs to handle.
        std::cout<< "(( registering URLs. ))" << std::endl;
        w32::http::Session session(version);
        w32::http::Group group(session);
        group.add("http://127.0.0.1:81/");
        std::cout<< "(( binding queue. ))" << std::endl;
        group.bind(queue);
        
        std::cout<< "(( allocating buffer. ))" << std::endl;
        w32::http::Request request(4096);
        
        std::cout<< "(( fetching request. ))" << std::endl;
        queue.get(request);
        if ( request.verb() == GET )
        {
            std::cout << "  -- GET: " << request.resource() << std::endl;
            
            const w32::astring OK("OK");
            const w32::astring type("text/html");
            const w32::astring reply("<em>yeah!</em>");
            std::cout << "  -- chunk: " << (void*)reply.data() << std::endl;
            
            /*w32::http::Chunk content
                ((void*)reply.data(), (w32::ulong)reply.size());*/
            w32::http::Response response;
            response.status(200, OK);
            response.add(ContentType, type);
            //response.add(content);
            HTTP_DATA_CHUNK chunk;
            chunk.DataChunkType = HttpDataChunkFromMemory;
            const char * message = "Hey! You hit the server \r\n";
            chunk.FromMemory.pBuffer = (void*)message;
            chunk.FromMemory.BufferLength = strlen(message);
            response.data().EntityChunkCount = 1;
            response.data().pEntityChunks = &chunk;
            queue.put(request, response);
        }
        if ( request.verb() == POST )
        {
            std::cout << "  -- POST: " << std::endl;
        }
        std::cout << "  -- verb: " << request.verb() << std::endl;
        
        std::cout << "(( done. ))" << std::endl;
        std::cin.get();
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
