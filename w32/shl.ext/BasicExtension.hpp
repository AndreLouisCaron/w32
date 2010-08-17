#ifndef _w32_shl_ext_BasicExtension_hpp__
#define _w32_shl_ext_BasicExtension_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Object.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief COM wrapper for shell extension implementations.
         *
         * BasicExtension<SomeCustomExtension> will generate the darn overrides
         * for COM primitive wrappers, which allows you to only implement the
         * required methods to achieve functionaly and forget about the details.
         */
    template<typename Implementation>
    class /*W32_SHL_EXT_EXPORT*/ BasicExtension :
        public com::Object,
        public Implementation
    {
        /* overrides. */
    public:
            // Overloaded to avoid ambiguous resolution.
        ::ULONG __stdcall AddRef () {
            return (com::Object::AddRef());
        }

            // Overloaded to avoid ambiguous resolution.
        ::ULONG __stdcall Release () {
            return (com::Object::Release());
        }

            // Automagically perform interface casts for whatever known
            // extension interface.
        ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            )
        {
                // Make sure all of what happens below works properly.
            *object = 0;
            
                // Add a test for each known extension interface. This isn't
                // efficicent but isn't called often either.
            if ( guid == IID_IColumnProvider ) {
                w32::gdi::messagebox("QueryInterface()", "IColumnProvider");
                *object = dynamic_cast<::IColumnProvider*>(this);
            }
            else if ( guid == IID_IContextMenu ) {
                w32::gdi::messagebox("QueryInterface()", "IContextMenu");
                *object = dynamic_cast<::IContextMenu*>(this);
            }
            else if ( guid == IID_IContextMenu2 ) {
                w32::gdi::messagebox("QueryInterface()", "IContextMenu2");
                *object = dynamic_cast<::IContextMenu2*>(this);
            }
            else if ( guid == IID_IContextMenu3 ) {
                w32::gdi::messagebox("QueryInterface()", "IContextMenu3");
                *object = dynamic_cast<::IContextMenu3*>(this);
            }
            else if ( guid == IID_ICopyHookW ) {
                w32::gdi::messagebox("QueryInterface()", "ICopyHookW");
                *object = dynamic_cast<::ICopyHookW*>(this);
            }
            else if ( guid == IID_IDropTarget ) {
                w32::gdi::messagebox("QueryInterface()", "IDropTarget");
                *object = dynamic_cast<::IDropTarget*>(this);
            }
            else if ( guid == IID_IExtractIcon ) {
                w32::gdi::messagebox("QueryInterface()", "IExtractIcon");
                *object = dynamic_cast<::IExtractIcon*>(this);
            }
            else if ( guid == IID_IExtractImage ) {
                w32::gdi::messagebox("QueryInterface()", "IExtractImage");
                *object = dynamic_cast<::IExtractImage*>(this);
            }
            else if ( guid == IID_IExtractImage2 ) {
                w32::gdi::messagebox("QueryInterface()", "IExtractImage2");
                *object = dynamic_cast<::IExtractImage2*>(this);
            }
            else if ( guid == IID_IInitializeWithFile ) {
                w32::gdi::messagebox("QueryInterface()", "IInitializeWithFile");
                *object = dynamic_cast<::IInitializeWithFile*>(this);
            }
            else if ( guid == IID_IInitializeWithItem ) {
                w32::gdi::messagebox("QueryInterface()", "IInitializeWithItem");
                *object = dynamic_cast<::IInitializeWithItem*>(this);
            }
            else if ( guid == IID_IInitializeWithStream ) {
                *object = dynamic_cast<::IInitializeWithStream*>(this);
            }
            else if ( guid == IID_IPersistFile ) {
                w32::gdi::messagebox("QueryInterface()", "IPersistFile");
                *object = dynamic_cast<::IPersistFile*>(this);
            }
            else if ( guid == IID_IQueryInfo ) {
                w32::gdi::messagebox("QueryInterface()", "IQueryInfo");
                *object = dynamic_cast<::IQueryInfo*>(this);
            }
            else if ( guid == IID_IShellExtInit ) {
                w32::gdi::messagebox("QueryInterface()", "IShellExtInit");
                *object = dynamic_cast<::IShellExtInit*>(this);
            }
            else if ( guid == IID_IShellIconOverlayIdentifier ) {
                w32::gdi::messagebox("QueryInterface()", "IShellIconOverlayIdentifier");
                *object = dynamic_cast<::IShellIconOverlayIdentifier*>(this);
            }
            else if ( guid == IID_IShellPropSheetExt ) {
                w32::gdi::messagebox("QueryInterface()", "IShellPropSheetExt");
                *object = dynamic_cast<::IShellPropSheetExt*>(this);
                /*if ( *object != 0 ) {
                    w32::gdi::messagebox("QueryInterface()", "Yee-haW!!");
                }*/
            }
            else if ( guid == IID_IThumbnailProvider ) {
                *object = dynamic_cast<::IThumbnailProvider*>(this);
            }
            
                // Check if *both* an interface identifier *and* an
                // implementation were found.
            if ( *object != 0 ) {
                AddRef();
                return (S_OK);
            }
            
                // If we haven't found anything, pass along to test for
                // IUnknown and the like.
            return (com::Object::QueryInterface(guid,object));
        }
    };

} } }

#endif /* _w32_shl_ext_BasicExtension_hpp__ */
