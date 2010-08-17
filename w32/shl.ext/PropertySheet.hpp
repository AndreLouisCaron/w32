#ifndef _w32_shl_ext_PropertySheet_hpp__
#define _w32_shl_ext_PropertySheet_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/in-process-server.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Translates into higher-order queries.
         */
    class W32_SHL_EXT_EXPORT PropertySheet :
        public ::IShellExtInit,
        public ::IShellPropSheetExt
    {
        /* nested types. */
    public:
        class W32_SHL_EXT_EXPORT PropertyPage :
            public w32::gdi::PropertySheet::PageInfo
        {
            /* construction. */
        public:
            PropertyPage ( PropertySheet& sheet );
        };

        /* data. */
    private:
        volatile ::LONG myReferenceCount;
        com::Ptr< ::IDataObject >  myDataObject;

        /* construction. */
    public:
        PropertySheet ()
            : myReferenceCount(1)
        {
            ::InterlockedIncrement(&GlobalObjectCount);
        }

        virtual ~PropertySheet () {
            ::InterlockedDecrement(&GlobalObjectCount);
        }

        /* methods. */
    public:
        com::Ptr< ::IDataObject > data () const {
            return (myDataObject);
        }

            // Adds property pages to the dialog that pops up when the user
            // right clicks on one of the selected files (with the extension we
            // registered for) in the explorer and askes for the properties.
        virtual com::Result Populate (
            w32::gdi::PropertySheet::PageAdder& add
            )
        {
            return (com::Result::success());
        }

        /* overrides. */
    public:
        ::ULONG __stdcall AddRef () {
            return (::InterlockedIncrement(&myReferenceCount));
        }

        ::ULONG __stdcall Release ()
        {
            if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
            {
                delete this;
                return (0);
            }
            return (myReferenceCount);
        }

        ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            )
        {
            (*object) = 0;
            
            com::Guid::String iface(guid);
            if ( guid == IID_IUnknown ) {
                (*object) = static_cast< ::IUnknown* >(
                    dynamic_cast< ::IShellExtInit* >(this));
            }
            else if ( guid == IID_IShellExtInit ) {
                (*object) = dynamic_cast< ::IShellExtInit* >(this);
            }
            else if ( guid == IID_IShellPropSheetExt ) {
                (*object) = dynamic_cast< ::IShellPropSheetExt *>(this);
            }
            
            if ( (*object) != 0 ) {
                AddRef();
                return (S_OK);
            }
            
            return (E_NOINTERFACE);
        }

        virtual ::HRESULT __stdcall Initialize (
            ::LPCITEMIDLIST identifier, ::IDataObject * object, ::HKEY key
            );

        virtual ::HRESULT __stdcall AddPages (
            ::LPFNADDPROPSHEETPAGE function, ::LPARAM parameter
            );

            // No need to implement this function.
        virtual ::HRESULT __stdcall ReplacePage (
            ::UINT page, ::LPFNADDPROPSHEETPAGE replace, ::LPARAM parameter
            );
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellExtInit > ()
{
    return (IID_IShellExtInit);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellPropSheetExt > ()
{
    return (IID_IShellPropSheetExt);
}


#endif /* _w32_shl_ext_PropertySheet_hpp__ */
