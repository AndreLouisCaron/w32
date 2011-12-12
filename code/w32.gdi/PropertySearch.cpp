// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/PropertySearch.hpp>
#include <w32.gdi/Window.hpp>

namespace {

    ::BOOL __stdcall EnumerationProcedure (
        ::HWND window, ::LPSTR name, ::HANDLE value, ::ULONG_PTR data
        )
    {
        w32::gdi::PropertySearch *const search =
            reinterpret_cast<w32::gdi::PropertySearch*>(data);
        try {
            search->result(name,value);
        }
            // Consume exceptions before returning control to the system.
        catch ( ... ) {}
        return (TRUE);
    }

}

namespace w32 { namespace gdi {

    void PropertySearch::enumerate ( const Window& owner )
    {
        const ::ULONG_PTR data = reinterpret_cast<::ULONG_PTR>(this);
        ::EnumPropsExA(owner.handle(), &::EnumerationProcedure, data);
    }

} }
