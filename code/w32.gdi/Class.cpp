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

#include <w32.gdi/Class.hpp>
#include <w32.gdi/Notification.hpp>
#include <w32.gdi/Brush.hpp>
#include <w32.gdi/Cursor.hpp>
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
