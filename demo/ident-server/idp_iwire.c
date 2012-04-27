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
 * @file idp_iwire.c
 * @brief Ident service query parser.
 */

#include "idp_iwire.h"
#include <ctype.h>

int idp_expect_server_port (idp_iwire * stream, const char * data, int size);
int idp_decode_server_port (idp_iwire * stream, const char * data, int size);
int idp_separator          (idp_iwire * stream, const char * data, int size);
int idp_expect_client_port (idp_iwire * stream, const char * data, int size);
int idp_decode_client_port (idp_iwire * stream, const char * data, int size);
int idp_expect_end_of_line (idp_iwire * stream, const char * data, int size);

static int idp_expect_end_of_line
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    if (used < size)
    {
        if (data[used] == '\n')
        {
            /* update parser statistics. */
            ++stream->queries;
            /* invoke callback, handle pause. */
            if (stream->query(stream)) {
                stream->error = idp_iwire_pause;
            }
            /* clear parser state, prepare for next query. */
            stream->server_port = 0;
            stream->client_port = 0;
            stream->state = &idp_expect_server_port;
            return (used+1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
       }
    }
    return (used);
}

static int idp_decode_client_port
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume client port number. */
    while ((used < size) && isdigit(data[used]))
    {
        /* accumulate client port value. */
        stream->client_port *= 10;
        stream->client_port += (data[used++]-'0');
        /* fail early on overflow. */
        if (stream->client_port > 65535) {
            stream->error = idp_iwire_invalid_client_port;
            return (used);
        }
    }
    if (used < size)
    {
        /* tolerate abbreviated line endings. */
        if (data[used] == '\n') {
            stream->state = &idp_expect_end_of_line;
            return (used);
        }
        /* expect DOS-style line ending. */
        if (data[used] == '\r') {
            stream->state = &idp_expect_end_of_line;
            return (used+1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (used);
}

static int idp_expect_client_port
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume whitespace. */
    while ((used < size) && isspace(data[used])) {
        ++used;
    }
    /* expect 1st digit for client port number. */
    if (used < size)
    {
        if (isdigit(data[used])) {
            stream->state = &idp_decode_client_port;
            return (used);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
            return (used);
        }
    }
    return (used);
}

static int idp_separator
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume whitespace. */
    while ((used < size) && isspace(data[used])) {
        ++used;
    }
    /* expect comma as argument separator. */
    if (used < size)
    {
        if (data[used] == ',') {
            stream->state = idp_expect_client_port;
            return (used+1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
            return (used);
        }
    }
    return (used);
}

static int idp_decode_server_port
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    while ((used < size) && isdigit(data[used]))
    {
        /* accumulate server port value. */
        stream->server_port *= 10;
        stream->server_port += (data[used++]-'0');
        /* fail early on overflow. */
        if (stream->server_port > 65535) {
            stream->error = idp_iwire_invalid_server_port;
            return (used);
        }
    }
    if (used < size)
    {
        /* fail on underflow. */
        if (stream->server_port < 1) {
            stream->error = idp_iwire_invalid_server_port;
            return (used);
        }
        /* quick fast-forward to client-port state. */
        if (data[used] == ',') {
            stream->state = &idp_expect_client_port;
            return (used+1);
        }
        /* tolerate whitespace before the separator. */
        if (isspace(data[used])) {
            stream->state = &idp_separator;
            return (used+1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (used);
}

static int idp_expect_server_port
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume whitespace. */
    while ((used < size) && isspace(data[used])) {
        ++used;
    }
    /* expect 1st digit for server port number. */
    if (used < size)
    {
        if (isdigit(data[used])) {
            stream->state = &idp_decode_server_port;
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (used);
}

static int idp_feed
    (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume as much data as possible. */
    while ((used < size) && (stream->error == idp_iwire_good)) {
        used += stream->state(stream, data+used, size-used);
    }
    /* unpause the parser if query() requested a pause. */
    if (stream->error == idp_iwire_pause) {
        stream->error = idp_iwire_good;
    }
    return (used);
}

void idp_iwire_init (idp_iwire * stream)
{
    stream->queries = 0;
    stream->baton   = 0;
    stream->query   = 0;
    stream->server_port = 0;
    stream->client_port = 0;
    stream->error = idp_iwire_good;
    stream->state = &idp_expect_server_port;
}

int idp_iwire_feed (idp_iwire * stream, const void * data, int size )
{
    return (idp_feed(stream, (const char*)data, size));
}
