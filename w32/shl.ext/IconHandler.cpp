// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl.ext/IconHandler.hpp>

namespace w32 { namespace shl { namespace ext {

    ::HRESULT __stdcall IconHandler::GetIconLocation (
        ::UINT flags, char *, ::UINT, int *, ::UINT * result
        )
    {
            // We will provide icon handles in the Extract() method.
        *result = GIL_DONTCACHE | GIL_NOTFILENAME | GIL_PERINSTANCE;
        
            // Make sure the extension wants to process this file.
        if ( !accepts() ) {
            *result = 0;
            return (S_FALSE);
        }
        
        return (S_OK);
    }

    ::HRESULT __stdcall IconHandler::Extract (
        const char *, ::UINT, ::HICON * big, ::HICON * small, ::UINT size
        )
    {
            // Size of icons.
        const w32::gdi::Size bigsize(LOWORD(size),LOWORD(size));
        const w32::gdi::Size smallsize(HIWORD(size),HIWORD(size));
        try {
                // The handles for resources are never freed.
            *big   = w32::gdi::Icon(this->big(),   bigsize  ).handle();
            *small = w32::gdi::Icon(this->small(), smallsize).handle();
        } catch ( ... ) {
            return (E_FAIL);
        }
        return (S_OK);
    }

    ::HRESULT __stdcall IconHandler::GetClassID ( ::CLSID * class_ )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall IconHandler::IsDirty ()
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall IconHandler::Load ( const wchar_t * file, ::DWORD mode )
    {
            // What does mode store?
        try {
            myFile = file;
        } catch ( const std::bad_alloc& ) {
            return (E_OUTOFMEMORY);
        } catch ( ... ) {
            return (E_FAIL);
        }
        return (S_OK);
    }

    ::HRESULT __stdcall IconHandler::Save(
        const wchar_t * file, ::BOOL remember
        )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall IconHandler::SaveCompleted ( const wchar_t * file )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall IconHandler::GetCurFile ( wchar_t ** file )
    {
        return (E_NOTIMPL);
    }

} } }
