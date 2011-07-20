// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Window.hpp>
#include <w32/gdi/Brush.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HWND create (
        ::LPCWSTR class_, ::DWORD extended, ::DWORD standard,
        const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, class_, 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, 0, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreateWindowEx,::GetLastError());
        }
        return (handle);
    }

    void release ( ::HWND object )
    {
        const ::BOOL result = ::DestroyWindow(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HWND )
    {
    }

    ::LONG_PTR get ( ::HWND handle, int index )
    {
            // GetWindowLongPtr() returns 0 both on failure and when the data
            // slot contained a null pointer. Moreover, it doesn't clear the
            // last error code on success.
        ::SetLastError(0);
        
        const ::LONG_PTR result = ::GetWindowLongPtr(handle, index);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != 0 ) {
                UNCHECKED_WIN32C_ERROR(GetWindowLongPtr, error);
            }
        }
        return (result);
    }

    ::LONG_PTR set ( ::HWND handle, int index, ::LONG_PTR value )
    {
            // SetWindowLongPtr() returns 0 both on failure and when the data
            // slot contained a null pointer. Moreover, it doesn't clear the
            // last error code on success.
        ::SetLastError(0);
        
        const ::LONG_PTR result = ::SetWindowLongPtr(handle, index, value);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != 0 ) {
                UNCHECKED_WIN32C_ERROR(SetWindowLongPtr, error);
            }
        }
        return (result);
    }

}

namespace w32 { namespace gdi {

    Window::Handle Window::claim ( ::HWND object )
    {
        return (Handle(object, &release));
    }

    Window::Handle Window::proxy ( ::HWND object )
    {
        return (Handle(object, &abandon));
    }

    Rectangle Window::adjust (
        const Rectangle& bounds, const Style& style
        )
    {
        ::RECT ajusted = bounds.data();
        const ::BOOL result = ::AdjustWindowRectEx(
            &ajusted, style.standard(), FALSE, style.extended()
            );
        return (Rectangle(ajusted));
    }

    Window::Window ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Window::Window (
        const Registration& class_, const Rectangle& bounds
        )
        : myHandle(Window::claim(
              ::create(class_.atom().raw(), 0, 0, bounds.data())
        ))
    {
    }

    Window::Window (
        const Registration& class_,
        const Rectangle& bounds, const Style& style
        )
        : myHandle(Window::claim(::create(
              class_.atom().raw(), style.extended(),
              style.standard(), bounds.data())
              ))
    {
    }

    Window::Window ( const Rectangle& bounds, const Style& style )
        : myHandle(Window::claim(
              ::create(L"static", style.extended(),
              style.standard(), bounds.data())
              ))
    {
    }

    const Window::Handle& Window::handle () const
    {
        return (myHandle);
    }

    void Window::invalidate ()
    {
            // Ask to receive a WM_PAINT message for the entire area.
        if ( ::InvalidateRect(handle(),0,FALSE) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(InvalidateRect,::GetLastError());
        }
    }

    void Window::invalidate ( const Rectangle& area )
    {
            // Ask to receive a WM_PAINT message for the requested area.
        if ( ::InvalidateRect(handle(),&area.data(),FALSE) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(InvalidateRect,::GetLastError());
        }
    }

    void Window::show ()
    {
        ::ShowWindow(handle(),SW_SHOW);
    }

    void Window::show ( const Animation& animation )
    {
        const ::BOOL result = ::AnimateWindow(
            handle(), 200, animation.value()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(AnimateWindow,::GetLastError());
        }
    }

    void Window::hide ()
    {
        ::ShowWindow(handle(),SW_HIDE);
    }

    void Window::hide ( const Animation& animation )
    {
        const ::BOOL result = ::AnimateWindow(
            handle(), 200, AW_HIDE | animation.value()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(AnimateWindow,::GetLastError());
        }
    }

    void Window::enable ()
    {
            // Might return TRUE or FALSE depending
            // if the window was enabled or not.
        ::EnableWindow(handle(),TRUE);
    }

    void Window::disable ()
    {
            // Might return TRUE or FALSE depending
            // if the window was enabled or not.
        ::EnableWindow(handle(),FALSE);
    }

    void Window::minimize ()
    {
        ::ShowWindow(handle(),SW_SHOWMINIMIZED);
    }

    void Window::maximize ()
    {
        ::ShowWindow(handle(),SW_SHOWMAXIMIZED);
    }

    void Window::restore ()
    {
        ::ShowWindow(handle(),SW_RESTORE);
    }

    bool Window::minimized () const
    {
        return (::IsIconic(handle()) != FALSE);
    }

    bool Window::maximized () const
    {
        return (::IsZoomed(handle()) != FALSE);
    }

    void Window::region ( const Region& region )
    {
        const ::BOOL result = ::SetWindowRgn(
            handle(), region.handle(), TRUE
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SetWindowRgn,::GetLastError());
        }
    }

    void Window::bounds ( const Rectangle& area )
    {
        const ::BOOL result = ::MoveWindow(
            handle(), area.left(), area.top(),
            area.width(), area.height(), FALSE
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(MoveWindow,::GetLastError());
        }
    }

    const Rectangle Window::bounds () const
    {
        ::RECT area;
        if ( ::GetWindowRect(handle(),&area) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(GetWindowRect,::GetLastError());
        }
        return (Rectangle(area));
    }

    const Rectangle Window::area () const
    {
        ::RECT area;
        if ( ::GetClientRect(handle(),&area) == FALSE ) {
            UNCHECKED_WIN32C_ERROR(GetClientRect,::GetLastError());
        }
        return (Rectangle(area));
    }

#if (defined(MICROSOFT_COMPILER))
#   pragma warning ( push )
#   pragma warning ( disable : 4244 )
#endif
    void Window::extra ( void * pointer )
    {
        ::SetWindowLongPtrA(
            handle(), GWL_USERDATA, ::LONG_PTR(pointer)
            );
    }

    void * Window::extra () const
    {
        return ((void*)::GetWindowLongPtrA(handle(),GWL_USERDATA));
    }

#if (defined(MICROSOFT_COMPILER))
#   pragma warning ( pop )
#endif

    void Window::focus ()
    {
        if ( ::SetFocus(handle()) == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFocus,::GetLastError());
        }
    }

    void Window::font ( const Font& font )
    {
        const ::WPARAM handle =
            reinterpret_cast< ::WPARAM >((::HFONT)font.handle());
        const ::LPARAM redraw = TRUE;
        const ::LRESULT result = ::SendMessageW(
            this->handle(), WM_SETFONT, handle, redraw);
            // There is no documented return value.
    }

    Font Window::font () const
    {
        const ::LRESULT result = ::SendMessageW(handle(), WM_GETFONT, 0, 0);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetWindowFont, ::GetLastError());
        }
        const Font::Handle handle(reinterpret_cast< ::HFONT >(result));
        return (Font(handle));
    }

    void Window::background ( const Brush& brush )
    {
            // SetWindowLongPtr() returns 0 both on failure and when the data
            // slot contained a null pointer. Moreover, it doesn't clear the
            // last error code on success.
        ::SetLastError(0);
        
        const ::HBRUSH handle = brush.handle();
        const ::ULONG_PTR result = ::SetClassLongPtrW(
            this->handle(), GCLP_HBRBACKGROUND,
            reinterpret_cast< ::ULONG_PTR >(handle)
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error != 0 ) {
                UNCHECKED_WIN32C_ERROR(SetClassLongPtr, error);
            }
        }
    }

    Icon Window::bigicon () const
    {
#if 0
        const ::LRESULT result  = ::SendMessage(
            handle(), WM_GETICON, ICON_BIG, 0
            );
        return (IconProxy(reinterpret_cast<::HICON>(result)));
#else
        const ::LONG_PTR result = ::GetClassLongPtr(handle(), GCL_HICON);
        const Icon::Handle handle(Icon::proxy(reinterpret_cast<::HICON>(result)));
        return (Icon(handle));
#endif
    }

    Icon Window::smallicon () const
    {
#if 0
        const ::LRESULT result  = ::SendMessage(
            handle(), WM_GETICON, ICON_SMALL, 0
            );
        return (IconProxy(reinterpret_cast<::HICON>(result)));
#else
        const ::LONG_PTR result = ::GetClassLongPtr(handle(), GCL_HICONSM);
        const Icon::Handle handle(Icon::proxy(reinterpret_cast<::HICON>(result)));
        return (Icon(handle));
#endif
    }

    void Window::icon ( const Icon& icon )
    {
        const ::LRESULT result  = ::SendMessage(
            handle(), WM_SETICON, ICON_SMALL,
            reinterpret_cast< ::LPARAM >((::HICON)icon.handle())
            );
    }

    void Window::text ( const string& text )
    {
        const ::BOOL result =::SetWindowTextW(handle(), text.data());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SetWindowText, ::GetLastError());
        }
    }

    Window::Callback Window::callback () const
    {
        return (reinterpret_cast<Callback>(::get(handle(), GWL_WNDPROC)));
    }

    Window::Callback Window::callback ( Callback callback )
    {
        return (reinterpret_cast<Callback>(::set(handle(), GWL_WNDPROC,
            reinterpret_cast< ::LONG_PTR >(callback))));
    }

    Window::Style Window::style () const
    {
        const ::DWORD standard = ::get(handle(), GWL_STYLE);
        const ::DWORD extended = ::get(handle(), GWL_EXSTYLE);
        return (Style(standard, extended));
    }

    void Window::style ( const Window::Style& style )
    {
        ::set(handle(), GWL_STYLE, style.standard());
        ::set(handle(), GWL_EXSTYLE, style.extended());
    }

    Window::Style::Style ()
        : myStandard(0), myExtended(0)
    {
    }

} }
