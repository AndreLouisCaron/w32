// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/WindowEvents.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    WindowEvents::WindowEvents ( const Window& window )
        : myWindow(window)
    {
    }

    const Window& WindowEvents::window () const
    {
        return (myWindow);
    }

    bool WindowEvents::next ( Event& event, Filter filter )
    {
        const ::BOOL result = ::GetMessage(
            &event.data(), myWindow.handle(), filter.first(), filter.last()
            );
        if ( result == -1 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMessage, error);
        }
        return (result != 0);
    }

    bool WindowEvents::peek ( Event& event, Filter filter )
    {
        const ::BOOL result = ::PeekMessage(
            &event.data(), myWindow.handle(),
            filter.first(), filter.last(), PM_NOREMOVE
            );
        return (result != FALSE);
    }

    void WindowEvents::post ( const Message& message )
    {
        const ::BOOL result = ::PostMessage(
            myWindow.handle(), message.wm(), message.wp(), message.lp()
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(PostMessage,::GetLastError());
        }
    }

} }
