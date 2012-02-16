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

#include <w32.shl.ext/ThumbnailHandler.hpp>
#include <w32/Error.hpp>
#include <memory>
#include <stdio.h>

namespace {

    ::HBITMAP copy
        ( const w32::gdi::Bitmap& image, const w32::gdi::Size& size )
    {
        return (0);
    }

}

namespace w32 { namespace shl { namespace ext {

    w32::gdi::Size ThumbnailHandler::adjust (
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

    bool ThumbnailHandler::readonly () const
    {
        return (myMode == STGM_READ);
    }

    const string& ThumbnailHandler::path () const
    {
        return (myPath);
    }

    ThumbnailHandler::Priority ThumbnailHandler::priority () const
    {
        return (Priority::maximum());
    }

    ::HRESULT __stdcall ThumbnailHandler::GetClassID ( ::CLSID * class_ )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ThumbnailHandler::IsDirty ()
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ThumbnailHandler::Load ( ::LPCWSTR path, ::DWORD mode )
    try
    {
        myPath = path;
        myMode = mode;
        return (S_OK);
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( const w32::Error& error ) {
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall ThumbnailHandler::Save(
        ::LPCWSTR path, ::BOOL remember
        )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ThumbnailHandler::SaveCompleted ( ::LPCWSTR path )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ThumbnailHandler::GetCurFile ( ::LPWSTR * path )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ThumbnailHandler::Extract ( ::HBITMAP * bitmap )
    try
    {
        *bitmap = ::copy(fetch(),w32::gdi::Size(0,0));
        return (S_OK);
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( const w32::Error& error ) {
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall ThumbnailHandler::GetLocation (
        ::LPWSTR path, ::DWORD length, ::DWORD * priority,
        const ::SIZE * size, ::DWORD depth, ::DWORD * flags
        )
    try
    {
            // Sanity checks.
        if ((priority == 0) || (flags == 0) || (size == 0)) {
            return (E_INVALIDARG);
        }

            // Return the path to the image, if requested.
        if ((path != 0) && (length > 0))
        {
                // This is apparently not necessary to implement and doesn't
                // make any sense, because the path is passed to us through
                // IPersistFile::Load() and then queried here...
            const int result = ::_snwprintf(path,length-1,L"%s",myPath.data());
            path[result] = L'\0';
        }

            // Remove the path for the moment...
        path[0] = L'\0';

            // Set the priority for this image, even if we don't extract
            // asynchronously: it's safe and foolproof.
        *priority = this->priority().value();

            // Display items properly even if the aspect ratio is non-standard.
        *flags |= IEIFLAG_ORIGSIZE;

            // Ask the implementation to compute the thumbnail right away.
        compute(w32::gdi::Size(*size),depth);

        return (S_OK);
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( const w32::Error& error ) {
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall ThumbnailHandler::GetDateStamp ( ::FILETIME * stamp )
    try
    {
        return (E_NOTIMPL);
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( const w32::Error& error ) {
        return (HRESULT_FROM_WIN32(error.code()));
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    const ThumbnailHandler::Priority ThumbnailHandler::Priority::maximum ()
    {
        return (IEI_PRIORITY_MAX);
    }

    const ThumbnailHandler::Priority ThumbnailHandler::Priority::normal ()
    {
        return (IEIT_PRIORITY_NORMAL);
    }

    const ThumbnailHandler::Priority ThumbnailHandler::Priority::minimum ()
    {
        return (IEI_PRIORITY_MIN);
    }

    ThumbnailHandler::Priority::Priority ( Value value )
        : myValue(value)
    {
    }

    ThumbnailHandler::Priority::Value ThumbnailHandler::Priority::value () const
    {
        return (myValue);
    }

} } }
