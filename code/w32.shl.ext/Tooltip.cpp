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

#include <w32.shl.ext/Tooltip.hpp>
#include <w32.com/Allocator.hpp>

namespace w32 { namespace shl { namespace ext {

    ::HRESULT __stdcall Tooltip::GetInfoFlags ( ::DWORD * )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Tooltip::GetInfoTip (
        ::DWORD, ::LPWSTR * tip
        )
    {
            // Allocate and return information string.
        try {
            const w32::bstring content = text();
            com::Allocator allocator;
            *tip = allocator.acquire<wchar_t>(content.size());
            ::wcscpy(*tip,content.data());
        } catch ( const std::bad_alloc& ) {
            return (E_OUTOFMEMORY);
        } catch ( ... ) {
            return (E_FAIL);
        }
        return (S_OK);
    }

    ::HRESULT __stdcall Tooltip::GetClassID ( ::LPCLSID class_ )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Tooltip::IsDirty ()
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Tooltip::Load (
        ::LPCOLESTR file, ::DWORD mode
        )
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

    ::HRESULT __stdcall Tooltip::Save(
        ::LPCOLESTR file, ::BOOL remember
        )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Tooltip::SaveCompleted ( ::LPCOLESTR file )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Tooltip::GetCurFile ( ::LPOLESTR * file )
    {
        return (E_NOTIMPL);
    }

} } }
