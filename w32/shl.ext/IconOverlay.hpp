#ifndef _w32_shl_ext_IconOverlay_hpp__
#define _w32_shl_ext_IconOverlay_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Shell extension that dynamically assigns icons to items in
         *    the Windows Explorer.
         *
         * If you want to define icon overlays, you should implement the
         * \c IconOverlayOverlay class instead.
         */
    class W32_SHL_EXT_EXPORT IconOverlay :
        public ::IShellIconOverlayIdentifier
    {
        /* nested types. */
    public:
        class W32_SHL_EXT_EXPORT Priority
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
