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

#include <w32.shl.ext/PropertySheet.hpp>
#include <w32.shl/Dropping.hpp>

namespace {

        // This is called to release the reference to our COM object when
        // the page is destroyed by the property sheet.
    ::UINT __stdcall PageDestroyed (
        ::HWND, ::UINT message, ::LPPROPSHEETPAGEW page
        )
    {
        if ( message == PSPCB_RELEASE ) {
            reinterpret_cast<::IUnknown*>(page->lParam)->Release();
        }
        return (TRUE);
    }

        // Event handler for the dialog page.
    ::INT_PTR __stdcall DialogProcedure (
        ::HWND dialog, ::UINT message, ::WPARAM wparam, ::LPARAM lparam
        )
    {
            // See SetProp(), GetProp() and RemoveProp() functions for
            // associating IDs to controls? Wrap in <w32.gdi/...>.
        if ( message == WM_INITDIALOG )
        {
                // Fetch a pointer to the property page.
            const ::LPPROPSHEETPAGEW page =
                reinterpret_cast< ::LPPROPSHEETPAGEW >(lparam);
            
                // Extract the pointer to our wrapper object (we passed along).
            const w32::shl::ext::PropertySheet * extension =
                  reinterpret_cast< w32::shl::ext::PropertySheet* >(page->lParam);
            
                // Store that pointer inside the property sheet itself for later
                // use (we won't have access to the creation data afterwards).
            ::SetWindowLongPtr(dialog,DWLP_USER,lparam);
            
                // Fetch combo box control.
            w32::gdi::ComboBox combobox(
                w32::gdi::Window::claim(::GetDlgItem(dialog, 0)));
            
                // Show a list of the dropped files.
            const w32::shl::Data data(extension->data());
            const w32::shl::Dropping files(data);
            for ( w32::uint i = 0; i < files.count(); ++i ) {
                combobox.append(files[i]);
            }
        }
        else if ( message == PSCB_PRECREATE )
        {
        }
        #if 0
        else if ( message == WM_DESTROY ) {
        }
        else if ( message == WM_COMMAND ) {
        }
        #endif
        else if ( message == WM_NOTIFY )
        {
                // Obtain the pointer to the property sheet page we stored
                // in the dialog's custom user data field.
            ::LPPROPSHEETPAGE psp = reinterpret_cast<::LPPROPSHEETPAGE>(
                ::GetWindowLongPtr(dialog,DWLP_USER)
                );
        }
        else {
            return (FALSE);
        }

            // Calling "::DefDlgProc(dialog,message,wparam,lparam)" crashes
            // the explorer: simply indicate which messages are processed.
        return (TRUE);
    }

}

namespace w32 { namespace shl { namespace ext {

    PropertySheet::PropertyPage::PropertyPage ( PropertySheet& sheet )
    {
        callback(&::PageDestroyed);
        dialog(&::DialogProcedure);
        parameter(&sheet);
    }

    ::HRESULT __stdcall PropertySheet::Initialize (
        ::LPCITEMIDLIST identifier, ::IDataObject * object, ::HKEY key
        )
    {
        if ( object != 0 ) {
            myDataObject = com::manage(object);
        }
        if (identifier != 0) {
            w32::gdi::messagebox("Initialize", "Path to item provided.");
        }
        if (key != 0) {
            //w32::gdi::messagebox("Initialize", "Program ID key provided.");
        }
        return (S_OK);
    }

    ::HRESULT __stdcall PropertySheet::AddPages (
        ::LPFNADDPROPSHEETPAGE function, ::LPARAM parameter
        )
    {
        w32::gdi::PropertySheet::PageAdder add(function,parameter);
        const com::Result result = Populate(add);
        if ( result.good() ) {
            dynamic_cast<::IShellPropSheetExt*>(this)->AddRef();
        }
        return (result.value());
    }

        // Apparently only used for control panel property sheet extensions.
    ::HRESULT __stdcall PropertySheet::ReplacePage (
        ::UINT page, ::LPFNADDPROPSHEETPAGE replace, ::LPARAM parameter
        )
    {
        w32::gdi::messagebox("PropertySheet","ReplacePage()");
        return (E_NOTIMPL);
    }

} } }
