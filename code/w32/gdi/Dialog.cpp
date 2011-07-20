// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Dialog.hpp>
#include <iostream>
#include <memory>
#include <utility>

namespace {

    ::HWND create ( ::HMODULE module, ::LPCDLGTEMPLATE dialog )
    {
        const ::HWND handle = ::CreateDialogIndirect(
            module, dialog, 0, 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateDialogIndirect, error);
        }
        return (handle);
    }

    template<typename T>
    class temporary_buffer
    {
        std::pair<T*,std::ptrdiff_t> myBackend;

        temporary_buffer ( const temporary_buffer& );
        temporary_buffer& operator= ( const temporary_buffer& );

    public:
        temporary_buffer ( std::ptrdiff_t length )
            : myBackend(std::get_temporary_buffer<T>(length))
        {
            if ( myBackend.first == 0 ) {
                throw (std::bad_alloc());
            }
        }

        ~temporary_buffer ()
        {
            std::return_temporary_buffer(begin());
        }

        T * begin () const
        {
            return (myBackend.first);
        }

        T * end () const
        {
            return (begin() + size());
        }

        std::ptrdiff_t size () const
        {
            return (myBackend.second);
        }
    };

        // Event loop for modal dialogs.
    ::INT_PTR __stdcall DialogProcedure (
        ::HWND handle, ::UINT message, ::WPARAM wparam, ::LPARAM lparam
        )
    {
        if ( message == WM_INITDIALOG ) {
            return (TRUE);
        }
        else if ( message == WM_COMMAND ) {
            return (TRUE);
        }
        else if ( message == WM_CLOSE )
        {
            ::EndDialog(handle,1);
            return (TRUE);
        }
        return (FALSE);
    }

        // Pop a modal dialog box from a resource template.
    ::INT_PTR direct
        ( ::HMODULE module, ::LPCWSTR name, ::HWND parent, ::DLGPROC callback )
    {
        const ::INT_PTR result = ::DialogBoxW(module, name, parent, callback);
        if ( result == static_cast<::INT_PTR>(result) ) {
            UNCHECKED_WIN32C_ERROR(DialogBox,::GetLastError());
        }
        return (result);
    }

        // Pops a modal dialog box from an in-memory template.
    ::INT_PTR indirect
    ( const ::DLGTEMPLATE * template_, ::HWND parent, ::DLGPROC callback )
    {
        const ::INT_PTR result = ::DialogBoxIndirect(
                                     0, template_, parent, callback
                                 );
        if ( result == static_cast<::INT_PTR>(-1) ) {
            UNCHECKED_WIN32C_ERROR(DialogBox,::GetLastError());
        }
        return (result);
    }

        // Aligns the pointer to the next DWORD boundary, as required.
    template<typename Pointer>
    Pointer align ( Pointer value, int N )
    {
        return (reinterpret_cast<Pointer>(
                    (reinterpret_cast<w32::uintptr>(value) + (N-1)) & ~(N-1)
                ));
    }

        // Output a string past a buffer.
    ::WORD * write ( ::WORD * position, const wchar_t * string )
    {
        while ( *position++ = static_cast<::WORD>(*string++) )
            ;
        return (position);
    }

    ::BYTE * write ( ::BYTE * position, const wchar_t * string )
    {
        return (reinterpret_cast<::BYTE*>(write(
            reinterpret_cast<::WORD*>(position), string
            )));
    }

        // Writes a control-class id.
    ::WORD * write ( ::WORD * position, ::WORD low, ::WORD high )
    {
        *position++ = low, *position++ = high;
        return (position);
    }

    ::BYTE * write ( ::BYTE * position, ::WORD low, ::WORD high )
    {
        return (reinterpret_cast<::BYTE*>(write(
            reinterpret_cast<::WORD*>(position), low, high
            )));
    }

}

namespace w32 { namespace gdi {

    Dialog::Result Dialog::show ( const Resource& template_ )
    {
        return (show(template_, &::DialogProcedure));
    }

    Dialog::Result Dialog::show ( const Resource& template_, Callback callback )
    {
        const ::HMODULE module = template_.module().handle();
        const ::LPCWSTR name = template_.identifier();
        return (::direct(module, name, 0, callback));
    }

    Dialog::Result Dialog::show (
        const Window& parent, const Resource& template_
        )
    {
        return (show(parent, template_, &::DialogProcedure));
    }

    Dialog::Result Dialog::show (
        const Window& parent, const Resource& template_, Callback callback
        )
    {
        const ::HMODULE module = template_.module().handle();
        const ::LPCWSTR name = template_.identifier();
        return (::direct(
            module, name, parent.handle(), callback));
    }

    Dialog::Result Dialog::show ( const Template& template_ )
    {
        return (show(template_, &::DialogProcedure));
    }

    Dialog::Result Dialog::show ( const Template& template_, Callback callback )
    {
        return (::indirect(&template_.data(), 0, callback));
    }

    Dialog::Result Dialog::show (
        const Window& parent, const Template& template_
        )
    {
        return (show(parent, template_, &::DialogProcedure));
    }

    Dialog::Result Dialog::show (
        const Window& parent, const Template& template_, Callback callback
        )
    {
        return (::indirect(
            &template_.data(), parent.handle(), callback));
    }

    Dialog::Dialog ( const Handle& handle )
        : Window(handle)
    {
    }

    Dialog::Dialog ( const Template& template_, const Module& module )
        : Window(Window::claim(
        ::create(module.handle(), &template_.data())
        ))
    {
    }

    void Dialog::end ( intptr status )
    {
        const ::BOOL result = ::EndDialog(handle(), status);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EndDialog, error);
        }
    }

    lresult Dialog::send ( word identifier, uint msg, wparam wp, lparam lp )
    {
        return (::SendDlgItemMessageW(
            handle(), identifier, msg, wp, lp));
    }

    bool Dialog::checked ( word identifier ) const
    {
        return (::SendDlgItemMessageW(
            handle(), identifier, BM_GETCHECK, 0, 0) == BST_CHECKED);
    }

    bool Dialog::unchecked ( word identifier ) const
    {
        return (::SendDlgItemMessageW(
            handle(), identifier, BM_GETCHECK, 0, 0) == BST_UNCHECKED);
    }

    string Dialog::caption ( word identifier ) const
    {
            // Use fast allocation technique.
        temporary_buffer<wchar_t> buffer(1024);
        
        ::UINT result = 0;
        do {
                // Fetch value.
            result = ::GetDlgItemTextW(
                handle(), identifier, buffer.begin(), buffer.size()
                );
            
                // Check for errors.
            if ( result == 0 )
            {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(GetDlgItemText, error);
            }
            
            // Check for string truncation.
        } while ( result == (buffer.size()-1) ); // TODO: REALLOCATE!
        
            // Allocate a real string.
        return (string(buffer.begin()));
    }

    void Dialog::caption ( word identifier, const string& text )
    {
        const ::BOOL result = ::SetDlgItemTextW(
            handle(), identifier, text.c_str()
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetDlgItemText, error);
        }
    }

    Dialog::Template::Template (
        byte * buffer, const Rectangle& bounds,
        uint8 items, const string& title
        )
        : myStart(buffer), myPosition(myStart)
    {
            // Write DLGTEMPLATE structure in memory.
        ::DLGTEMPLATE * header = reinterpret_cast<::DLGTEMPLATE*>(myPosition);
        header->style =
            WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION | DS_MODALFRAME | DS_SETFONT;
        header->dwExtendedStyle = 0;
        header->x = static_cast<word>(bounds.origin().x());
        header->y = static_cast<word>(bounds.origin().y());
        header->cx = static_cast<word>(bounds.span().width());
        header->cy = static_cast<word>(bounds.span().height());
        header->cdit = items;
        myPosition += sizeof(::DLGTEMPLATE);
        
            // No menu.
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(WORD);
        
            // Default dialog class.
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
            // Window title.
        myPosition = write(myPosition, title.data());
        
            // Font size & name.
        *reinterpret_cast<word*>(myPosition) = 8;
        myPosition += sizeof(word);
        myPosition = write(myPosition, L"Tahoma");
    }

    Dialog::Template::~Template ()
    {
        // free memory...
    }

    Dialog::Template& Dialog::Template::button (
        const Rectangle& area, const string& caption, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE | BS_TEXT | BS_PUSHBUTTON | BS_DEFPUSHBUTTON;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"button");
        
            // Write text-button caption.
        myPosition = write(myPosition, caption.data());
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::checkbox (
        const Rectangle& area, const string& caption, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE | BS_TEXT | BS_AUTOCHECKBOX | BS_NOTIFY;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"button");
        
            // Write text-button caption.
        myPosition = write(myPosition, caption.data());
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::edit (
        const Rectangle& area, const string& text, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_LEFT | ES_WANTRETURN | ES_MULTILINE;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"edit");
        
            // Add label text.
        myPosition = write(myPosition, text.data());
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::label (
        const Rectangle& area, const string& text, word identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE | SS_LEFT;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"static");
        
            // Add label text.
        myPosition = write(myPosition, text.data());
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::listbox (
        const Rectangle& area, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"listbox");
        
            // No initial value.
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(WORD);
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::scrollbar (
        const Rectangle& area, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"scrollbar");
        
            // No initial value.
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(WORD);
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

    Dialog::Template& Dialog::Template::combobox (
        const Rectangle& area, uint8 identifier
        )
    {
            // This structure MUST be aligned on a DWORD boundary.
        myPosition = align(myPosition, sizeof(dword));
        
            // Write DLGITEMTEMPLATE structure in memory.
        ::DLGITEMTEMPLATE *const header =
            reinterpret_cast<::DLGITEMTEMPLATE*>(myPosition);
        header->style =
            WS_CHILD | WS_VISIBLE;
        header->dwExtendedStyle = 0;
        header->id = identifier;
        header->x = static_cast<word>(area.origin().x());
        header->y = static_cast<word>(area.origin().y());
        header->cx = static_cast<word>(area.span().width());
        header->cy = static_cast<word>(area.span().height());
        myPosition += sizeof(::DLGITEMTEMPLATE);
        
            // Write the name of the control class we want to instantiate.
        myPosition = write(myPosition, L"combobox");
        
             // No initial value.
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(WORD);
        
            // Add other creation data (none).
        *reinterpret_cast<word*>(myPosition) = 0;
        myPosition += sizeof(word);
        
        return (*this);
    }

} }
