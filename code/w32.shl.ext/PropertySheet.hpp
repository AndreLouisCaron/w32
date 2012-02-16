#ifndef _w32_shl_ext_PropertySheet_hpp__
#define _w32_shl_ext_PropertySheet_hpp__

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
#include <w32/app/in-process-server.hpp>

namespace w32 { namespace shl { namespace ext {

        /*!
         * @brief Translates into higher-order queries.
         */
    class PropertySheet :
        public ::IShellExtInit,
        public ::IShellPropSheetExt
    {
        /* nested types. */
    public:
        class PropertyPage :
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
