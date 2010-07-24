// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/gdi/WindowEvents.hpp>
#include <win32c/diagnostics/UncheckedError.hpp>

namespace win32c { namespace gdi {

    WindowEvents::WindowEvents ( const Window& window )
        : myWindow(window)
    {
    }

    const Window& WindowEvents::window () const
    {
        return (myWindow);
    }

    bool WindowEvents::next ( Event& event, const Filter& filter )
    {
        const ::BOOL result = ::GetMessage(
            &event.data(), myWindow.handle().get(),
            filter.first(), filter.last()
            );
        if ( result == -1 ) {
            UNCHECKED_WIN32C_ERROR(GetMessage,::GetLastError());
        }
        return (result != 0);
    }

    bool WindowEvents::peek ( Event& event, const Filter& filter )
    {
        const ::BOOL result = ::PeekMessage(
            &event.data(), myWindow.handle().get(),
            filter.first(), filter.last(), PM_NOREMOVE
            );
        return (result != 0);
    }

    void ThreadEvents::post ( const Notification& notification )
    {
        const ::BOOL result = ::PostMessage(
            myWindow.handle(), notification.message(),
            notification.wparam(), notification.lparam()
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(PostMessage,::GetLastError());
        }
    }

} }
