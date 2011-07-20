#ifndef _w32_shl_ext_ContextMenu_hpp__
#define _w32_shl_ext_ContextMenu_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl.ext/Extension.hpp>

namespace w32 { namespace shl { namespace ext {

    class ContextMenu :
        virtual public Extension,
        public ::IContextMenu
    {
        /* methods. */
    public:
            // Adds menu items to the context menu that pops up when the user
            // right clicks on one of the selected files (with the extension we
            // registered for) in the explorer.
        virtual w32::uint Populate (
            w32::gdi::Menu& menu, w32::uint position,
            w32::uint first, w32::uint last
            )
        {
            return (0);
        }

            // Invoke the command the user clicked on in the menu. The value
            // we receive is the 0-based index of the commands we added in the
            // call to Populate().
        virtual com::Result Invoke ( w32::word item )
        {
            return (com::Result::failure());
        }

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall QueryContextMenu (
            ::HMENU menu, ::UINT index, ::UINT first, ::UINT last, ::UINT flags
            );

        virtual ::HRESULT __stdcall GetCommandString (
            ::UINT command, ::UINT flags, ::UINT *, ::LPSTR text, ::UINT limit
            );

        virtual ::HRESULT __stdcall InvokeCommand (
            ::LPCMINVOKECOMMANDINFO command
            );
    };

} } }

#endif /* _w32_shl_ext_ContextMenu_hpp__ */
