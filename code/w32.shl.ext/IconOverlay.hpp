#ifndef _w32_shl_ext_IconOverlay_hpp__
#define _w32_shl_ext_IconOverlay_hpp__

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

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Shell extension that dynamically assigns icons to items in
         *    the Windows Explorer.
         *
         * If you want to define icon overlays, you should implement the
         * \c IconOverlayOverlay class instead.
         */
    class IconOverlay :
        public ::IShellIconOverlayIdentifier
    {
        /* nested types. */
    public:
        class Priority
        {
            /* class data. */
        public:
            static const Priority lowest;
            static const Priority lower;
            static const Priority standard;
            static const Priority higher;
            static const Priority highest;

            /* data. */
        private:
            int myValue;

            /* construction. */
        private:
            Priority ( int value );

            /* methods. */
        public:
            int value () const;
        };

        /* methods. */
    public:
        virtual Priority priority () const;

        virtual bool accepts (
            const w32::bstring& path, const w32::fs::Attributes& attributes
            ) const = 0;

        virtual const w32::Resource& overlay () const = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall GetOverlayInfo (
            wchar_t * file, int length, int * index, ::DWORD * result
            );
        virtual ::HRESULT __stdcall GetPriority ( int * priority );
        virtual ::HRESULT __stdcall IsMemberOf (
            const wchar_t * path, ::DWORD attributes
            );
    };

} } }

#endif /* _w32_shl_ext_IconOverlay_hpp__ */
