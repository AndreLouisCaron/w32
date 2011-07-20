// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl.ext/Tooltip.hpp>
#include <w32/com/Allocator.hpp>

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
