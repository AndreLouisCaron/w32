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

#include <w32.gdi/Cursor.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HCURSOR load ( ::LPCWSTR path )
    {
        const ::HANDLE handle = ::LoadImageW(
            0, path, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE
            );
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(LoadImage,::GetLastError());
        }
        return (reinterpret_cast< ::HCURSOR >(handle));
    }

    ::HCURSOR fetch ( ::LPCSTR cursor )
    {
        const ::HCURSOR handle = ::LoadCursorA(0, cursor);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadCursor, error);
        }
        return (handle);
    }

    void destroy ( ::HCURSOR object )
    {
        if ( ::DestroyCursor(object) == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HCURSOR object )
    {
    }

}

namespace w32 { namespace gdi {

    Cursor::Handle Cursor::claim ( ::HCURSOR object )
    {
        return (Cursor::Handle(object, &::destroy));
    }

    Cursor::Handle Cursor::proxy ( ::HCURSOR object )
    {
        return (Cursor::Handle(object, &::abandon));
    }

    const Cursor Cursor::appstarting ()
    {
        return (Cursor(claim(::fetch(IDC_APPSTARTING))));
    }

    const Cursor Cursor::arrow ()
    {
        return (Cursor(claim(::fetch(IDC_ARROW))));
    }

    const Cursor Cursor::cross ()
    {
        return (Cursor(claim(::fetch(IDC_CROSS))));
    }

    const Cursor Cursor::hand ()
    {
        return (Cursor(claim(::fetch(IDC_HAND))));
    }

    const Cursor Cursor::ibeam ()
    {
        return (Cursor(claim(::fetch(IDC_IBEAM))));
    }

    const Cursor Cursor::no ()
    {
        return (Cursor(claim(::fetch(IDC_NO))));
    }

    const Cursor Cursor::sizeall ()
    {
        return (Cursor(claim(::fetch(IDC_SIZEALL))));
    }

    const Cursor Cursor::sizenesw ()
    {
        return (Cursor(claim(::fetch(IDC_SIZENESW))));
    }

    const Cursor Cursor::sizens ()
    {
        return (Cursor(claim(::fetch(IDC_SIZENS))));
    }

    const Cursor Cursor::sizenwse ()
    {
        return (Cursor(claim(::fetch(IDC_SIZENWSE))));
    }

    const Cursor Cursor::sizewe ()
    {
        return (Cursor(claim(::fetch(IDC_SIZEWE))));
    }

    const Cursor Cursor::up ()
    {
        return (Cursor(claim(::fetch(IDC_ARROW))));
    }

    const Cursor Cursor::wait ()
    {
        return (Cursor(claim(::fetch(IDC_WAIT))));
    }

    Cursor::Cursor ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Cursor::Cursor ( const string& path )
        : myHandle(claim(::load(path.c_str())))
    {
    }

    const Cursor::Handle& Cursor::handle () const
    {
        return (myHandle);
    }

} }
