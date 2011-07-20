// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl.ext/ContextMenu.hpp>

namespace w32 { namespace shl { namespace ext {

    ::HRESULT __stdcall ContextMenu::QueryContextMenu (
        ::HMENU menu, ::UINT index, ::UINT first, ::UINT last, ::UINT flags
        )
    {
        w32::gdi::Menu context(w32::gdi::Menu::proxy(menu));
        if ( (flags & (CMF_NORMAL|CMF_EXPLORE)) != 0 ) {
            ::UINT items = Populate(context,index,first,last);
            return (MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,items));
        }
        return (MAKE_HRESULT(SEVERITY_SUCCESS,FACILITY_NULL,0));
    }

    ::HRESULT __stdcall ContextMenu::GetCommandString (
        ::UINT command, ::UINT flags, ::UINT *, ::LPSTR text, ::UINT limit
        )
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall ContextMenu::InvokeCommand (
        ::LPCMINVOKECOMMANDINFO command
        )
    {
        if ( HIWORD(command->lpVerb) != 0 ) {
            return (E_INVALIDARG);
        }
        return (Invoke(LOWORD(command->lpVerb)).value());
    }

} } }
