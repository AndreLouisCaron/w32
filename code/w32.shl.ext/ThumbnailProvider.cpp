// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
