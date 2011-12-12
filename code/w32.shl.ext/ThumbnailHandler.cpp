// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
