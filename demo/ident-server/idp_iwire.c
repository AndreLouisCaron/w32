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

/* auxiliary states. */
int idp_reset (idp_iwire * stream, const char * data, int size);
int idp_space (idp_iwire * stream, const char * data, int size);
int idp_comma (idp_iwire * stream, const char * data, int size);
int idp_colon (idp_iwire * stream, const char * data, int size);
int idp_eolcr (idp_iwire * stream, const char * data, int size);
int idp_eollf (idp_iwire * stream, const char * data, int size);
int idp_match (idp_iwire * stream, const char * data, int size);

/* main states. */
int idp_sport (idp_iwire * stream, const char * data, int size);
int idp_cport (idp_iwire * stream, const char * data, int size);

int idp_query (idp_iwire * stream, const char * data, int size);

int idp_rtype (idp_iwire * stream, const char * data, int size);
int idp_split (idp_iwire * stream, const char * data, int size);
int idp_etype (idp_iwire * stream, const char * data, int size);
int idp_ecode (idp_iwire * stream, const char * data, int size);
int idp_error (idp_iwire * stream, const char * data, int size);

int idp_opsys (idp_iwire * stream, const char * data, int size);
int idp_codec (idp_iwire * stream, const char * data, int size);
int idp_token (idp_iwire * stream, const char * data, int size);
int idp_reply (idp_iwire * stream, const char * data, int size);

static int idp_feed (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* consume as much data as possible. */
    while ((used < size) && (stream->error == idp_iwire_good)) {
        used += stream->stack[stream->level](stream, data+used, size-used);
    }
    /* each parser is paused is applied only once. */
    if (stream->error == idp_iwire_pause) {
        stream->error = idp_iwire_good;
    }
    return (used);
}

void idp_iwire_init (idp_iwire * stream, enum idp_iwire_mode mode)
{
    /* parser statistics. */
    stream->messages = 0;

    /* callback state. */
    stream->mode         = mode;
    stream->baton        = 0;
    stream->accept_query = 0;
    stream->accept_opsys = 0;
    stream->accept_codec = 0;
    stream->accept_token = 0;
    stream->accept_reply = 0;

    /* public fields. */
    stream->server_port  = 0;
    stream->client_port  = 0;
    stream->error = idp_iwire_good;

    /* pattern matching stuff. */
    stream->text = "", stream->base = 0;

    /* initial state. */
    stream->stack[0] = idp_sport;
    stream->stack[1] = idp_space;
    stream->level = 1;
}

int idp_iwire_feed (idp_iwire * stream, const void * data, int size )
{
    return (idp_feed(stream, (const char*)data, size));
}

static int idp_reset (idp_iwire * stream, const char * data, int size)
{
    stream->server_port = 0;
    stream->client_port = 0;
    stream->stack[0] = idp_sport;
    stream->stack[1] = idp_space;
    stream->level = 1;
    return (0);
}

static int idp_space (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    while ((used < size) && isspace(data[used])) {
        ++used;
    }
    if (used < size) {
        --stream->level;
    }
    return (used);
}

static int idp_comma (idp_iwire * stream, const char * data, int size)
{
    if (size > 0)
    {
        if (data[0] == ',') {
            --stream->level; return (1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (0);
}

static int idp_colon (idp_iwire * stream, const char * data, int size)
{
    if (size > 0)
    {
        if (data[0] == ':') {
            --stream->level; return (1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (0);
}

static int idp_eollf (idp_iwire * stream, const char * data, int size)
{
    int level = stream->level;
    if (size > 0)
    {
        if (data[0] == '\n')
        {
            /* pop off all non-consuming "commit" states at the end. */
            while (level-- > 0) {
                stream->stack[--stream->level](stream, "", 0);
            }
            return (1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (0);
}

static int idp_eolcr (idp_iwire * stream, const char * data, int size)
{
    if (size > 0)
    {
        /* tolerate abbreviated line feed. */
        if (data[0] == '\n') {
            --stream->level; return (0);
        }
        if (data[0] == '\r') {
            --stream->level; return (1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (0);
}

static int idp_match (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    while ((used < size) && (stream->text[stream->base] != '\0'))
    {
        if (data[used] == stream->text[stream->base]) {
            ++used, ++stream->base;
        }
        else {
            stream->error = idp_iwire_invalid_syntax; break;
        }
    }
    if (stream->text[stream->base] == '\0') {
        --stream->level;
    }
    return (used);
}

static int idp_reply (idp_iwire * stream, const char * data, int size)
{
    /* update parser statistics. */
    ++stream->messages;
    /* invoke callback, handle pause. */
    if (stream->accept_reply(stream)) {
        stream->error = idp_iwire_pause;
    }
    /* clear parser state, prepare for next query. */
    return (idp_reset(stream, data, size));
}

static int idp_sport (idp_iwire * stream, const char * data, int size)
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
            stream->stack[0] = idp_cport;
            stream->stack[1] = idp_space;
            stream->level = 1;
            return (used+1);
        }
        /* tolerate whitespace before and after the separator. */
        if (isspace(data[used])) {
            stream->stack[0] = idp_cport;
            stream->stack[1] = idp_space;
            stream->stack[2] = idp_comma;
            stream->stack[3] = idp_space;
            stream->level = 3;
            return (used+1);
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (used);
}

static int idp_cport (idp_iwire * stream, const char * data, int size)
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
        /* queries and replies are handled differently after the port pair. */
        if (stream->mode == idp_iwire_query)
        {
            stream->stack[0] = idp_reset;
            stream->stack[1] = idp_query;
            stream->stack[2] = idp_eollf;
            stream->stack[3] = idp_eolcr;
            stream->level = 3;
        }
        else {
            stream->stack[0] = idp_rtype;
            stream->stack[1] = idp_space;
            stream->stack[2] = idp_colon;
            stream->stack[3] = idp_space;
            stream->level = 3;
        }
    }
    return (used);
}

static int idp_query (idp_iwire * stream, const char * data, int size)
{
    /* update parser statistics. */
    ++stream->messages;
    /* invoke callback, handle pause. */
    if (stream->accept_query(stream)) {
        stream->error = idp_iwire_pause;
    }
    /* clear parser state, prepare for next query. */
    return (idp_reset(stream, data, size));
}

static int idp_rtype (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* select reply type. */
    if ((used < size) && (stream->base == 0))
    {
        if (data[used] == 'U') {
            ++used, ++stream->base, stream->text = "USERID";
        }
        if (data[used] == 'E') {
            ++used, ++stream->base, stream->text = "ERROR";
        }
        if (stream->base > 0) {
            stream->stack[0] = idp_split;
            stream->stack[1] = idp_match;
            stream->level = 1;
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
        }
    }
    return (used);
}

static int idp_split (idp_iwire * stream, const char * data, int size)
{
    /* dispatch based on response type. */
    if (stream->text[0] == 'U') {
        stream->stack[0] = idp_opsys;
    }
    else {
        stream->stack[0] = idp_etype;
    }
    stream->stack[1] = idp_space;
    stream->stack[2] = idp_colon;
    stream->stack[3] = idp_space;
    stream->level = 3;
    /* clear pattern. */
    stream->text = "", stream->base = 0;
    return (0);
}

static int idp_etype (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    if (data[used] == 'X') {
        stream->stack[0] = idp_reset;
        stream->stack[1] = idp_error;
        stream->level = 1;
    }
    else if (size > 0)
    {
        if (data[used] == 'I') {
            ++used, ++stream->base, stream->text = "INVALID-PORT";
        }
        else if (data[used] == 'N') {
            ++used, ++stream->base, stream->text = "NO-USER";
        }
        else if (data[used] == 'U') {
            ++used, ++stream->base, stream->text = "UNKNOWN-ERROR";
        }
        else if (data[used] == 'H') {
            ++used, ++stream->base, stream->text = "HIDDEN-USER";
        }
        else {
            stream->error = idp_iwire_invalid_syntax;
            return (used);
        }
        stream->stack[0] = idp_reset;
        stream->stack[1] = idp_ecode;
        stream->stack[2] = idp_match;
        stream->level = 2;
    }
    return (used);
}

static int idp_ecode (idp_iwire * stream, const char * data, int size)
{
    /* forward error identifier. */
    stream->accept_error(stream, stream->text, stream->base);
    stream->accept_error(stream, "", 0);
    /* clear pattern. */
    stream->text = "", stream->base = 0;
    --stream->level;
    return (0);
}

static int idp_error (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* forward non-whitespace data. */
    while ((used < size) && !isspace(data[used])) {
        ++used;
    }
    if (used > 0) {
        stream->accept_error(stream, data, used);
    }
    if (used < size) {
        stream->accept_error(stream, "", 0), --stream->level;
    }
    return (used);
}

int idp_opsys (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    while ((used < size) && !isspace(data[used])
           && (data[used] != ',') && (data[used] != ':'))
    {
        ++used;
    }
    if (used > 0) {
        stream->accept_opsys(stream, data, used);
    }
    if (used < size)
    {
        if (data[used] == ',') {
            ++used, stream->stack[0] = idp_codec, stream->level = 0;
        }
        else {
            stream->accept_codec(stream, "US-ASCII", 8);
            stream->stack[0] = idp_token;
            stream->stack[1] = idp_space;
            stream->stack[2] = idp_colon;
            stream->stack[3] = idp_space;
            stream->level = 3;
        }
    }
    return (used);
}

static int idp_codec (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    while ((used < size) && !isspace(data[used]) && (data[used] != ':')) {
        ++used;
    }
    if (used > 0) {
        stream->accept_codec(stream, data, used);
    }
    if (used < size) {
        stream->stack[0] = idp_token;
        stream->stack[1] = idp_space;
        stream->stack[2] = idp_colon;
        stream->stack[3] = idp_space;
        stream->level = 3;
    }
    return (used);
}

static int idp_token (idp_iwire * stream, const char * data, int size)
{
    int used = 0;
    /* forward all bytes until end of line. */
    while ((used < size) && (data[used] != '\r')) {
        ++used;
    }
    if (used > 0) {
        stream->accept_token(stream, data, used);
    }
    if (used < size) {
        stream->stack[0] = idp_reply;
        stream->stack[1] = idp_eollf;
        stream->stack[2] = idp_eolcr;
        stream->level = 2;
    }
    return (used);
}
