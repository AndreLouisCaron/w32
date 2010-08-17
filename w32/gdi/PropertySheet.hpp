#ifndef _w32_gdi_PropertySheet_hpp__
#define _w32_gdi_PropertySheet_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Resource.hpp>
#include <w32/Error.hpp>
#include <w32/gdi/Control.hpp>
#include <w32/gdi/Dialog.hpp>

namespace w32 { namespace gdi {

    class W32_GDI_EXPORT PropertySheet :
        virtual public Control
    {
        /* nested types. */
    public:
        class PageInfo;
        class Page;
        class PageAdder;

        /* methods. */
    public:
    };

    class W32_GDI_EXPORT PropertySheet::PageInfo :
        private w32::NotCopyable
    {
        /* data. */
    protected:
        ::PROPSHEETPAGEW myData;

        /* construction. */
    protected:
        PageInfo ()
        {
            ::ZeroMemory(&myData,sizeof(myData));
            myData.dwSize = sizeof(myData);
        }

        /* methods. */
    public:
        const ::PROPSHEETPAGEW& get () const {
            return (myData);
        }

        void title ( const wchar_t * value ) {
            myData.dwFlags |= PSP_USETITLE;
            myData.pszTitle = value;
        }

        void callback ( ::LPFNPSPCALLBACKW function ) {
            myData.dwFlags |= PSP_USECALLBACK;
            myData.pfnCallback = function;
        }

        void template_ ( const Resource& template_ )
        {
            myData.hInstance = template_.module().handle();
            myData.pszTemplate = template_.identifier();
        }

        void template_ ( const Dialog::Template& template_ )
        {
            myData.dwFlags = PSP_DLGINDIRECT;
            myData.pResource = &template_.data();
        }

        void icon ( const w32::gdi::Icon& image ) {
            myData.dwFlags |= PSP_USEHICON;
            myData.hIcon = image.handle();
        }

        void dialog ( ::DLGPROC procedure ) {
            myData.pfnDlgProc = procedure;
        }

        void parameter ( void * pointer ) {
            myData.lParam = reinterpret_cast<::LPARAM>(pointer);
        }
    };

    class W32_GDI_EXPORT PropertySheet::Page :
        private w32::NotCopyable
    {
        /* data. */
    private:
        ::HPROPSHEETPAGE myHandle;

        /* construction. */
    public:
        Page ( const PageInfo& info )
            : myHandle(::CreatePropertySheetPageW(&info.get()))
        {
            if ( myHandle == 0 ) {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(CreatePropertySheetPage,error);
            }
        }

        ~Page ()
        {
            ::DestroyPropertySheetPage(myHandle);
        }

        /* methods. */
    public:
        ::HPROPSHEETPAGE handle () const {
            return (myHandle);
        }
    };

        /*!
         * @brief Simplifies the use of page-adding callbacks.
         */
    class W32_GDI_EXPORT PropertySheet::PageAdder
    {
        /* data. */
    private:
        ::LPFNADDPROPSHEETPAGE myFunction;
        ::LPARAM myParameter;

        /* construction. */
    public:
        PageAdder ( ::LPFNADDPROPSHEETPAGE function, ::LPARAM parameter )
            : myFunction(function), myParameter(parameter)
        {}

        /* operators. */
    public:
        void operator() ( const Page& page )
        {
            const ::BOOL result = myFunction(
                page.handle(), myParameter
                );
            if ( result == FALSE ) {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(AddPropSheetPageCallback,error);
            }
        }

        void operator() ( const PageInfo& info )
        {
                // Create a page that will automagically be destroyed.
            const ::HPROPSHEETPAGE page = ::CreatePropertySheetPageW(
                &info.get()
                );
            if ( page == 0 ) {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(CreatePropertySheetPage,error);
            }

                // Add it!
            const ::BOOL result = myFunction(page,myParameter);
            if ( result == FALSE ) {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(AddPropSheetPageCallback,error);
            }
        }
    };

} }

#endif /* _w32c_gdi_PropertySheet_hpp__ */
