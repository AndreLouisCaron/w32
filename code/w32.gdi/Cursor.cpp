// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
