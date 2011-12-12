
#include <w32.gdi/Foreground.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    void foreground ( const Window& window )
    {
        const ::BOOL result = ::SetForegroundWindow(window.handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetForegroundWindow, error);
        }
    }

    Window foreground ()
    {
        return (Window(Window::proxy(::GetForegroundWindow())));
    }

    Foreground::Foreground ( const Window& window )
        : myPredecessor(foreground())
    {
        foreground(window);
    }

    Foreground::~Foreground ()
    {
        foreground(myPredecessor);
    }

} }
