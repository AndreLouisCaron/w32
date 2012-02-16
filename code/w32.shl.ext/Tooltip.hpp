#ifndef _w32_shl_ext_Tooltip_hpp__
#define _w32_shl_ext_Tooltip_hpp__

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

        /*!
         * @brief Bubble of text displayed when the mouse hovers over certain
         *    items in the Windows Explorer.
         */
    class Tooltip :
        virtual public Extension,
        public ::IPersistFile,
        public ::IQueryInfo
    {
        /* data. */
    private:
        w32::bstring myFile;

        /* methods. */
    public:
            /*!
             * @brief Obtains the absolute path to the file over which the
             *    mouse is hovering.
             */
        const w32::bstring file () const {
            return (myFile);
        }

            /*!
             * @brief Obtains the text to display in the bubble.
             */
        virtual w32::bstring text () const = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall GetInfoFlags ( ::DWORD * );
        virtual ::HRESULT __stdcall GetInfoTip ( ::DWORD, ::LPWSTR * );

        virtual ::HRESULT __stdcall GetClassID ( ::LPCLSID class_ );
        virtual ::HRESULT __stdcall IsDirty ();
        virtual ::HRESULT __stdcall Load ( ::LPCOLESTR file, ::DWORD mode );
        virtual ::HRESULT __stdcall Save( ::LPCOLESTR file, ::BOOL remember );
        virtual ::HRESULT __stdcall SaveCompleted ( ::LPCOLESTR file );
        virtual ::HRESULT __stdcall GetCurFile ( ::LPOLESTR * file );
    };

} } }

#endif /* _w32_shl_ext_Tooltip_hpp__ */
