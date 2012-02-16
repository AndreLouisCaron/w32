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
