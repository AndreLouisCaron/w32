#ifndef _w32_shl_ext_ContextMenu_hpp__
#define _w32_shl_ext_ContextMenu_hpp__

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

#include "__configure__.hpp"
#include <w32.shl.ext/Extension.hpp>

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
