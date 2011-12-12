#ifndef _w32_shl_ext_DropTarget_hpp__
#define _w32_shl_ext_DropTarget_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.shl.ext/Extension.hpp>

namespace w32 { namespace shl { namespace ext {

    class DropTarget :
        virtual public Extension,
        public ::IPersistFile,
        public ::IDropTarget
    {
        /* methods. */
    public:

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall DragEnter (
            ::IDataObject * data, ::DWORD state, ::POINTL point, ::DWORD * effect
            );

        virtual ::HRESULT __stdcall DragOver (
            ::DWORD state, ::POINTL point, ::DWORD * effect
            );

        virtual ::HRESULT __stdcall DragLeave ();

        virtual ::HRESULT __stdcall Drop (
            ::IDataObject * data, ::DWORD state, ::POINTL point, ::DWORD * effect
            );

        virtual ::HRESULT __stdcall GetClassID ( ::LPCLSID class_ );

        virtual ::HRESULT __stdcall IsDirty ();

        virtual ::HRESULT __stdcall Load ( ::LPCOLESTR file, ::DWORD mode );

        virtual ::HRESULT __stdcall Save( ::LPCOLESTR file, ::BOOL remember );

        virtual ::HRESULT __stdcall SaveCompleted ( ::LPCOLESTR file );

        virtual ::HRESULT __stdcall GetCurFile ( ::LPOLESTR * file );
    };

} } }

#endif /* _w32_shl_ext_DropTarget_hpp__ */
