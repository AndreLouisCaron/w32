#ifndef _w32_shl_ext_IconHandler_hpp__
#define _w32_shl_ext_IconHandler_hpp__

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
         * @brief Shell extension that dynamically assigns icons to items in
         *    the Windows Explorer.
         *
         * If you want to define icon overlays, you should implement the
         * \c IconOverlayHandler class instead.
         */
    class IconHandler :
        virtual public Extension,
        public ::IPersistFile,
        public ::IExtractIcon
    {
        /* data. */
    private:
        string myFile;

        /* methods. */
    public:
            /*!
             * @brief Obtains the file name for which we want to obtain icons.
             */
        const string& file () const {
            return (myFile);
        }

            /*!
             * @brief Indicates if the icon handler should accept icon requests
             *    for the given file.
             *
             * You can write code that conditionally sets icons depending on
             * file size, contents, attributes, etc. This is a convenient hook
             * for refusing to assign icons to certain files.
             *
             * The default is to accept all files.
             *
             * @see file()
             */
        virtual bool accepts () const {
            return (true);
        }

            /*!
             * @brief Obtains the big icon.
             */
        virtual const w32::Resource& big () = 0;

            /*!
             * @brief Obtains the small icon.
             */
        virtual const w32::Resource& small () = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall GetIconLocation (
            ::UINT flags, char *, ::UINT, int *, ::UINT * result
            );
        virtual ::HRESULT __stdcall Extract (
            const char *, ::UINT, ::HICON * big, ::HICON * small, ::UINT size
            );

        virtual ::HRESULT __stdcall GetClassID ( ::CLSID * class_ );
        virtual ::HRESULT __stdcall IsDirty ();
        virtual ::HRESULT __stdcall Load (
            const wchar_t * file, ::DWORD mode
            );
        virtual ::HRESULT __stdcall Save(
            const wchar_t * file, ::BOOL remember
            );
        virtual ::HRESULT __stdcall SaveCompleted ( const wchar_t * file );
        virtual ::HRESULT __stdcall GetCurFile ( wchar_t ** file );
    };

} } }

#endif /* _w32_shl_ext_IconHandler_hpp__ */
