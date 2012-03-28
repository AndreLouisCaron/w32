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

#include <w32.http/Response.hpp>
#include <w32.http/Chunk.hpp>
#include <w32.http/Header.hpp>

namespace w32 { namespace http {

    Response::Response ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Response::Data& Response::data ()
    {
        return (myData);
    }

    const Response::Data& Response::data () const
    {
        return (myData);
    }

    void Response::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    void Response::status ( Status status, const astring& reason )
    {
        myData.StatusCode   = status;
        myData.pReason      = reason.data();
        myData.ReasonLength = reason.size();
    }

    void Response::add ( const http::Header& header, const astring& content )
    {
        myData.Headers.KnownHeaders[header].pRawValue      = content.data();
        myData.Headers.KnownHeaders[header].RawValueLength = content.size();
    }

    void Response::add ( const Header& header, const astring& content )
    {
        myData.Headers.KnownHeaders[header].pRawValue      = content.data();
        myData.Headers.KnownHeaders[header].RawValueLength = content.size();
    }

    void Response::add ( Chunk& chunk )
    {
        myData.pEntityChunks = &chunk.data();
        myData.EntityChunkCount = 1;
    }

    const Response::Header Response::Header::acceptranges ()
    {
        return (HttpHeaderAcceptRanges);
    }

    const Response::Header Response::Header::age ()
    {
        return (HttpHeaderAge);
    }

    const Response::Header Response::Header::etag ()
    {
        return (HttpHeaderEtag);
    }

    const Response::Header Response::Header::location ()
    {
        return (HttpHeaderLocation);
    }

    const Response::Header Response::Header::proxyauthenticate ()
    {
        return (HttpHeaderProxyAuthenticate);
    }

    const Response::Header Response::Header::retryafter ()
    {
        return (HttpHeaderRetryAfter);
    }

    const Response::Header Response::Header::server ()
    {
        return (HttpHeaderServer);
    }

    const Response::Header Response::Header::setcookie ()
    {
        return (HttpHeaderSetCookie);
    }

    const Response::Header Response::Header::vary ()
    {
        return (HttpHeaderVary);
    }

    const Response::Header Response::Header::wwwauthenticate ()
    {
        return (HttpHeaderWwwAuthenticate);
    }

    Response::Header::Header ( Value value )
        : myValue(value)
    {
    }

    Response::Header::operator Response::Header::Value () const
    {
        return (myValue);
    }

    bool Response::Header::operator== ( const Header& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Response::Header::operator!= ( const Header& rhs ) const
    {
        return (myValue != rhs.myValue);
    }

} }
