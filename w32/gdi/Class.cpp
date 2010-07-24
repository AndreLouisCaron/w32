// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Class.hpp>
#include <w32/gdi/Notification.hpp>
#include <w32/gdi/Brush.hpp>
#include <w32/gdi/Cursor.hpp>
#include <w32/Module.hpp>
#include <w32/Error.hpp>

namespace {

    ::LPARAM __stdcall WindowProcedure
        ( ::HWND window, ::UINT message, ::WPARAM wparam, ::LPARAM lparam )
    {
        //w32::gdi::Message m(message, wparam, lparam);
        /*w32::gdi::WindowProxy w(window);
        w32::gdi::Window::Handler& handler =
            *static_cast<w32::gdi::Window::Handler*>(w.extra());
        //handler.on();*/
        return (::DefWindowProcW(window, message, wparam, lparam));
    }

}

namespace w32 { namespace gdi {

    Class::Class ( const string& name )
        : myName(name), myData()
    {
        w32::Module module;
        ::ZeroMemory(&myData,sizeof(myData));
        myData.cbSize        = sizeof(myData);
        myData.lpfnWndProc   = &::WindowProcedure;
        myData.hInstance     = module.handle();
        myData.lpszClassName = myName.data();
        myData.hbrBackground = Brush::black().handle();
        myData.hCursor       = Cursor::arrow().handle();
    }

    void Class::style ( const Style& value )
    {
        myData.style = value.get();
    }

    Registration::Registration ( const Class& class_ )
        : myClass(class_), myAtom(::RegisterClassExW(&myClass.get()))
    {
        if ( myAtom.bad() ) {
            UNCHECKED_WIN32C_ERROR(RegisterClassEx,::GetLastError());
        }
    }

    Registration::~Registration ()
    {
        const ::BOOL result = ::UnregisterClassW(
            myClass.get().lpszClassName, myClass.get().hInstance
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(UnregisterClass,::GetLastError());
        }
    }

} }
