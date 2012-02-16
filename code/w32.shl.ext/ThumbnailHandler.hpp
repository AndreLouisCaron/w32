#ifndef _w32_shl_ext_ThumbnailHandler_hpp__
#define _w32_shl_ext_ThumbnailHandler_hpp__

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
         * @brief Extracts a thumbnail image for an item in the explorer.
         */
    class ThumbnailHandler :
        public ::IPersistFile,
        public ::IExtractImage // IExtractImage2 for caching.
    {
        /* nested types. */
    public:
        class Priority;

        /* data. */
    private:
        string myPath;
        dword myMode;

        /* class methods. */
    public:
            /*!
             * @brief Shinks \c actual into \c requested, maintaining aspect
             *    ratio.
             */
        static w32::gdi::Size adjust (
            const w32::gdi::Size& actual, const w32::gdi::Size& requested
            );

        /* methods */
    public:
            /*!
             * @brief Indicates if the item for which a thumbnail can only be
             *    read from, not written to.
             *
             * Although some items might not be read-only, you should not
             * modify the files for which thumbnails are requested: by
             * definition, this is just a "peek" at the file.
             */
        bool readonly () const;

            /*!
             * @brief Obtains the file name for which we want to obtain icons.
             */
        const string& path () const;

            /*!
             * @brief Obtains the priority of displaying this thumbnail.
             */
        virtual Priority priority () const;

            /*!
             * @brief Computes a thumbnail from the image file.
             */
        virtual void compute (
            const w32::gdi::Size& size, dword depth
            ) = 0;

            /*!
             * @brief Obtains the thumbnail previously computed.
             */
        virtual const w32::gdi::Bitmap& fetch () const = 0;

        /* overrides */
    public:
            // IPersistFile.
        virtual ::HRESULT __stdcall GetClassID ( ::CLSID * class_ );
        virtual ::HRESULT __stdcall IsDirty ();
        virtual ::HRESULT __stdcall Load (
            const wchar_t * path, ::DWORD mode
            );
        virtual ::HRESULT __stdcall Save(
            const wchar_t * path, ::BOOL remember
            );
        virtual ::HRESULT __stdcall SaveCompleted ( const wchar_t * path );
        virtual ::HRESULT __stdcall GetCurFile ( wchar_t ** path );

            // IExtractIcon.
        virtual ::HRESULT __stdcall Extract ( ::HBITMAP * bitmap );
        virtual ::HRESULT __stdcall GetLocation (
            ::LPWSTR path, ::DWORD length, ::DWORD * priority,
            const ::SIZE * size, ::DWORD depth, ::DWORD * flags
            );

            // IExtractIcon2.
        virtual ::HRESULT __stdcall GetDateStamp ( ::FILETIME * stamp );
    };

    class ThumbnailHandler::Priority
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
        static const Priority maximum ();
        static const Priority normal ();
        static const Priority minimum ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Priority ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

} } }

#endif /* _w32_shl_ext_ThumbnailHandler_hpp__ */
