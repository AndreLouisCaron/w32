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

#include <w32.shl.ext/ThumbnailProvider.hpp>
#include <w32/Error.hpp>
#include <algorithm>
#include <memory>

#define DEBUG(message) \
    w32::gdi::messagebox("ThumbnailProvider",message);

namespace w32 { namespace shl { namespace ext {

        // TODO: REMOVE!
    ::LONG GlobalObjectCount = 0;

    w32::gdi::Size ThumbnailProvider::adjust (
        const w32::gdi::Size& actual, const w32::gdi::Size& requested
        )
    {
        const int ratio = std::max(
            actual.width() / requested.width(),
            actual.height() / requested.height()
            );
        if ( ratio == 0 ) {
            return (actual);
        }
        return (w32::gdi::Size(actual.width()/ratio,actual.height()/ratio));
    }

    bool ThumbnailProvider::readonly () const
    {
        return (myMode == STGM_READ);
    }

    com::Ptr< ::IStream > ThumbnailProvider::stream () const
    {
        return (myStream);
    }

    ::HRESULT __stdcall ThumbnailProvider::GetThumbnail (
        ::UINT width, ::HBITMAP * bitmap, ::WTS_ALPHATYPE * alphatype
        )
    try
    {
        Alpha alpha = Alpha::unknown();
        compute(w32::gdi::Size(width,width),32);
        const w32::gdi::Bitmap& thumbnail = fetch();
        *bitmap = thumbnail.handle();
        *alphatype = alpha.value();

        return (S_OK);
    }
    catch ( const w32::Error& error ) {
        DEBUG("GetThumbnail: w3232 unchecked error!");
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        DEBUG("GetThumbnail: unknown failure!");
        return (E_FAIL);
    }

    ::HRESULT __stdcall ThumbnailProvider::Initialize (
        ::IStream * stream, ::DWORD mode
        )
    try
    {
        myMode = mode;
        myStream = com::manage(stream);
        return (S_OK);
    }
    catch ( const std::bad_alloc& ) {
        DEBUG("Initialize: out of memory!");
        return (E_OUTOFMEMORY);
    }
    catch ( const w32::Error& error ) {
        DEBUG("Initialize: w3232 unchecked error!");
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        DEBUG("Initialize: unknown failure!");
        return (E_FAIL);
    }

    const ThumbnailProvider::Alpha ThumbnailProvider::Alpha::unknown ()
    {
        return (WTSAT_UNKNOWN);
    }

    const ThumbnailProvider::Alpha ThumbnailProvider::Alpha::off ()
    {
        return (WTSAT_RGB);
    }

    const ThumbnailProvider::Alpha ThumbnailProvider::Alpha::on ()
    {
        return (WTSAT_ARGB);
    }

    ThumbnailProvider::Alpha::Alpha ( Value value )
        : myValue(value)
    {
    }

    ThumbnailProvider::Alpha::Value
        ThumbnailProvider::Alpha::value () const
    {
        return (myValue);
    }

} } }
