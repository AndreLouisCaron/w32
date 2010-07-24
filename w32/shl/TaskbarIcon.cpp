// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/TaskbarIcon.hpp>
#include <strsafe.h>

namespace w32 { namespace shl {

    TaskbarIcon::Message TaskbarIcon::creation ()
    {
        const ::UINT result = ::RegisterWindowMessageA("TaskbarCreated");
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(RegisterWindowMessage, ::GetLastError());
        }
        return (result);
    }

    TaskbarIcon::TaskbarIcon ( const Window& window, Identifier identifier )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbSize = sizeof(myData);
        myData.hWnd = window.handle();
        myData.uID = identifier;
    }

    TaskbarIcon::Data& TaskbarIcon::data ()
    {
        return (myData);
    }

    const TaskbarIcon::Data& TaskbarIcon::data () const
    {
        return (myData);
    }

    void TaskbarIcon::message ( Message value )
    {
        myData.uCallbackMessage = value;
        myData.uFlags |= NIF_MESSAGE;
    }

    void TaskbarIcon::tooltip ( const char * text )
    {
        ::StringCbCopyN(
            myData.szTip, sizeof(myData.szTip), text, sizeof(myData.szTip)
            );
        myData.uFlags |= NIF_TIP;
    }

    void TaskbarIcon::image ( const Image& image )
    {
        myData.hIcon = image.handle();
        myData.uFlags |= NIF_ICON;
    }

    void TaskbarIcon::add ( TaskbarIcon& icon )
    {
        if ( ::Shell_NotifyIconA(NIM_ADD, &icon.data()) == 0 ) {
            UNCHECKED_WIN32C_ERROR(Shell_NotifyIcon, 0);
        }
    }

    void TaskbarIcon::remove ( TaskbarIcon& icon )
    {
        const ::BOOL result = ::Shell_NotifyIconA(NIM_DELETE, &icon.data());
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(Shell_NotifyIcon, 0);
        }
    }

} }
