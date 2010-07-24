// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/WindowSearch.hpp>

namespace {

    ::BOOL __stdcall WindowEnumerationProcedure (
        ::HWND handle, ::LPARAM parameter
        )
    {
        const w32::gdi::Window window(w32::gdi::Window::proxy(handle));
        w32::gdi::WindowSearch& search =
            *reinterpret_cast< w32::gdi::WindowSearch* >(parameter);
        search.result(window);
        return (TRUE);
    }

}

namespace w32 { namespace gdi {

    void WindowSearch::perform ()
    {
        const ::BOOL result = ::EnumWindows(
            &WindowEnumerationProcedure,
            reinterpret_cast<::LPARAM>(this)
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32GDI_ERROR(EnumWindows, error);
        }
    }

} }
