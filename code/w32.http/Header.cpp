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

#include <w32.http/Header.hpp>

namespace w32 { namespace http {

    const Header Header::cachecontrol ()
    {
        return (HttpHeaderCacheControl);
    }

    const Header Header::connection ()
    {
        return (HttpHeaderConnection);
    }

    const Header Header::date ()
    {
        return (HttpHeaderDate);
    }

    const Header Header::keepalive ()
    {
        return (HttpHeaderKeepAlive);
    }

    const Header Header::pragma ()
    {
        return (HttpHeaderPragma);
    }

    const Header Header::trailer ()
    {
        return (HttpHeaderTrailer);
    }

    const Header Header::transferencoding ()
    {
        return (HttpHeaderTransferEncoding);
    }

    const Header Header::upgrade ()
    {
        return (HttpHeaderUpgrade);
    }

    const Header Header::via ()
    {
        return (HttpHeaderVia);
    }

    const Header Header::warning ()
    {
        return (HttpHeaderWarning);
    }

    const Header Header::allow ()
    {
        return (HttpHeaderAllow);
    }

    const Header Header::contentlength ()
    {
        return (HttpHeaderContentLength);
    }

    const Header Header::contenttype ()
    {
        return (HttpHeaderContentType);
    }

    const Header Header::contentencoding ()
    {
        return (HttpHeaderContentEncoding);
    }

    const Header Header::contentlanguage ()
    {
        return (HttpHeaderContentLanguage);
    }

    const Header Header::contentlocation ()
    {
        return (HttpHeaderContentLocation);
    }

    const Header Header::contentmd5 ()
    {
        return (HttpHeaderContentMd5);
    }

    const Header Header::contentrange ()
    {
        return (HttpHeaderContentRange);
    }

    const Header Header::expires ()
    {
        return (HttpHeaderExpires);
    }

    const Header Header::lastmodified ()
    {
        return (HttpHeaderLastModified);
    }

    Header::Header ( Value value )
        : myValue(value)
    {
    }

    Header::operator Header::Value () const
    {
        return (myValue);
    }

    bool Header::operator== ( const Header& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Header::operator!= ( const Header& rhs ) const
    {
        return (myValue != rhs.myValue);
    }

} }
