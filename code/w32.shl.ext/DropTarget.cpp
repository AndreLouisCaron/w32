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

#include <w32.shl.ext/DropTarget.hpp>

namespace w32 { namespace shl { namespace ext {

    ::HRESULT __stdcall DropTarget::DragEnter (
        ::IDataObject * data, ::DWORD state, ::POINTL point, ::DWORD * effect
        )
    {
            // Store list of dropped files.
        *effect = DROPEFFECT_NONE; // DROPEFFECT_COPY if ok?
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::DragOver (
        ::DWORD state, ::POINTL point, ::DWORD * effect
        )
    {
        *effect = DROPEFFECT_NONE;
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::DragLeave ()
    {
        return (S_OK);
    }

    ::HRESULT __stdcall DropTarget::Drop (
        ::IDataObject * data, ::DWORD state, ::POINTL point, ::DWORD * effect
        )
    {
            // Show options dialog.
        *effect = DROPEFFECT_NONE;
        return (S_OK);
    }

    ::HRESULT __stdcall DropTarget::GetClassID ( ::LPCLSID class_ )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::IsDirty ()
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::Load ( ::LPCOLESTR file, ::DWORD mode )
    {
            // No need to record path? Points to path of receiver?
        return (S_OK);
    }

    ::HRESULT __stdcall DropTarget::Save( ::LPCOLESTR file, ::BOOL remember )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::SaveCompleted ( ::LPCOLESTR file )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall DropTarget::GetCurFile ( ::LPOLESTR * file )
    {
        return (E_NOTIMPL);
    }

} } }
