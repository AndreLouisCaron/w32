// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/post.hpp>
#include <w32/gdi/Event.hpp>
#include <w32/gdi/Window.hpp>
#include <w32/mt/Thread.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    void post ( const Message& message )
    {
        const ::BOOL result = ::PostThreadMessageW(
            ::GetCurrentThreadId(), message.wm(),
            message.wp(), message.lp());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostThreadMessage, error);
        }
    }

    void post ( mt::Thread& thread, const Message& message )
    {
        const ::BOOL result = ::PostThreadMessageW(
            thread.identifier(), message.wm(),
            message.wp(), message.lp());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostThreadMessage, error);
        }
    }

    void post ( Window& window, const Message& message )
    {
        const ::BOOL result = ::PostMessageW(
            window.handle(), message.wm(),
            message.wp(), message.lp());
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostThreadMessage, error);
        }
    }

} }
