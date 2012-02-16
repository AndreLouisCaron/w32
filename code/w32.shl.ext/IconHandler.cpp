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

#include <w32.shl.ext/IconHandler.hpp>

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
