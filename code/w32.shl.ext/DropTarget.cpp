// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
