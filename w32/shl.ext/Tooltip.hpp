#ifndef _w32_shl_ext_Tooltip_hpp__
#define _w32_shl_ext_Tooltip_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl.ext/Extension.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Bubble of text displayed when the mouse hovers over certain
         *    items in the Windows Explorer.
         */
    class W32_SHL_EXT_EXPORT Tooltip :
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
