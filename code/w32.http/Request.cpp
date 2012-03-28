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

#include <w32.http/Request.hpp>
#include <w32.http/Verb.hpp>
#include <iostream>

namespace {

    void * acquire ( w32::size_t size )
    {
        return (operator new(size));
    }

    void destroy ( void * object )
    {
        operator delete(object);
    }

    ::HTTP_REQUEST_V2 * nasty_cast ( void * data )
    {
        return (static_cast< ::HTTP_REQUEST_V2* >(data));
    }

}

namespace w32 { namespace http {

    const Request::Id Request::null ()
    {
        return (HTTP_NULL_ID);
    }

    Request::Request ( size_t size )
        : mySize(size), myData(::acquire(mySize), &::destroy)
    {
    }

    Request::Data& Request::data ()
    {
        return (*::nasty_cast(myData));
    }

    const Request::Data& Request::data () const
    {
        return (*::nasty_cast(myData));
    }

    const size_t Request::size () const
    {
        return (mySize);
    }

    const Request::Id Request::id () const
    {
        return (data().RequestId);
    }

    const Verb Request::verb () const
    {
        return (Verb::of(*this));
    }

    const string Request::resource () const
    {
        const ::HTTP_COOKED_URL& url = data().CookedUrl;
        return (string(url.pAbsPath, url.AbsPathLength+url.QueryStringLength));
    }

    void Request::clear ()
    {
        //::ZeroMemory(myData, sizeof(myData));
    }

    const Request::Header Request::Header::accept ()
    {
        return (HttpHeaderAccept);
    }

    const Request::Header Request::Header::acceptcharset ()
    {
        return (HttpHeaderAcceptCharset);
    }

    const Request::Header Request::Header::acceptencoding ()
    {
        return (HttpHeaderAcceptEncoding);
    }

    const Request::Header Request::Header::acceptlanguage ()
    {
        return (HttpHeaderAcceptLanguage);
    }

    const Request::Header Request::Header::cookie ()
    {
        return (HttpHeaderCookie);
    }

    const Request::Header Request::Header::expect ()
    {
        return (HttpHeaderExpect);
    }

    const Request::Header Request::Header::from ()
    {
        return (HttpHeaderFrom);
    }

    const Request::Header Request::Header::host ()
    {
        return (HttpHeaderHost);
    }

    const Request::Header Request::Header::ifmatch ()
    {
        return (HttpHeaderIfMatch);
    }

    const Request::Header Request::Header::ifmodifiedsince ()
    {
        return (HttpHeaderIfModifiedSince);
    }

    const Request::Header Request::Header::maxforwards ()
    {
        return (HttpHeaderMaxForwards);
    }

    const Request::Header Request::Header::proxyauthorization ()
    {
        return (HttpHeaderProxyAuthorization);
    }

    const Request::Header Request::Header::referer ()
    {
        return (HttpHeaderReferer);
    }

    const Request::Header Request::Header::range ()
    {
        return (HttpHeaderRange);
    }

    const Request::Header Request::Header::te ()
    {
        return (HttpHeaderTe);
    }

    const Request::Header Request::Header::translate ()
    {
        return (HttpHeaderTranslate);
    }

    const Request::Header Request::Header::useragent ()
    {
        return (HttpHeaderUserAgent);
    }

    const Request::Header Request::Header::requestmaximum ()
    {
        return (HttpHeaderRequestMaximum);
    }

    Request::Header::Header ( Value value )
        : myValue(value)
    {
    }

    Request::Header::operator Request::Header::Value () const
    {
        return (myValue);
    }

    bool Request::Header::operator== ( const Header& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Request::Header::operator!= ( const Header& rhs ) const
    {
        return (myValue != rhs.myValue);
    }

} }
