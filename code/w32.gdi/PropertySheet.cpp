// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/PropertySheet.hpp>

namespace w32 { namespace gdi {

    PropertySheet::PageInfo::PageInfo ()
    {
       ::ZeroMemory(&myData,sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const ::PROPSHEETPAGEW& PropertySheet::PageInfo::get () const
    {
        return (myData);
    }

    void PropertySheet::PageInfo::title ( const wchar_t * value )
    {
        myData.dwFlags |= PSP_USETITLE;
        myData.pszTitle = value;
    }

    void PropertySheet::PageInfo::callback ( ::LPFNPSPCALLBACKW function )
    {
        myData.dwFlags |= PSP_USECALLBACK;
        myData.pfnCallback = function;
    }

    void PropertySheet::PageInfo::template_ ( const Resource& template_ )
    {
        myData.hInstance = template_.module().handle();
        myData.pszTemplate = template_.identifier();
    }

    void PropertySheet::PageInfo::template_
        ( const Dialog::Template& template_ )
    {
	myData.dwFlags = PSP_DLGINDIRECT;
	myData.pResource = &template_.data();
    }

    void PropertySheet::PageInfo::icon ( const w32::gdi::Icon& image )
    {
        myData.dwFlags |= PSP_USEHICON;
        myData.hIcon = image.handle();
    }

    void PropertySheet::PageInfo::dialog ( ::DLGPROC procedure )
    {
        myData.pfnDlgProc = procedure;
    }

    void PropertySheet::PageInfo::parameter ( void * pointer )
    {
        myData.lParam = reinterpret_cast<::LPARAM>(pointer);
    }

    PropertySheet::Page::Page ( const PageInfo& info )
        : myHandle(::CreatePropertySheetPageW(&info.get()))
    {
        if ( myHandle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePropertySheetPage,error);
        }
    }

    PropertySheet::Page::~Page ()
    {
        ::DestroyPropertySheetPage(myHandle);
    }

    ::HPROPSHEETPAGE PropertySheet::Page::handle () const
    {
        return (myHandle);
    }

    PropertySheet::PageAdder::PageAdder
        ( ::LPFNADDPROPSHEETPAGE function, ::LPARAM parameter )
        : myFunction(function), myParameter(parameter)
    {
    }

    void PropertySheet::PageAdder::operator() ( const Page& page )
    {
        const ::BOOL result = myFunction(
            page.handle(), myParameter
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(AddPropSheetPageCallback,error);
        }
    }

    void PropertySheet::PageAdder::operator() ( const PageInfo& info )
    {
        // Create a page that will automagically be destroyed.
        const ::HPROPSHEETPAGE page = ::CreatePropertySheetPageW(
            &info.get()
            );
        if ( page == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePropertySheetPage,error);
        }
        // Add it!
        const ::BOOL result = myFunction(page,myParameter);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(AddPropSheetPageCallback,error);
        }
    }

} }
