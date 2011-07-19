#ifndef _w32_shl_ext_ThumbnailHandler_hpp__
#define _w32_shl_ext_ThumbnailHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
