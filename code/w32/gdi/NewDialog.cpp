// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/NewDialog.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace {

    ::HWND create ( ::HMODULE module, ::LPCDLGTEMPLATE dialog )
    {
        const ::HWND handle = ::CreateDialogIndirect(
            module, dialog, 0, 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateDialogIndirect, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    NewDialog::NewDialog ( const Template& template_, const Module& module )
        : Window::Owner(::create(module.handle().value(), &template_.data()))
    {
    }

} }
