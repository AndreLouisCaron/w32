#ifndef _w32_gdi_Foreground_hpp__
#define _w32_gdi_Foreground_hpp__

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/gdi/Window.hpp>

namespace w32 { namespace gdi {

    W32_GDI_EXPORT void foreground ( const Window& window );
    W32_GDI_EXPORT Window foreground ();

    class W32_GDI_EXPORT Foreground :
        private NotCopyable
    {
        /* data. */
    private:
        Window myPredecessor;

        /* construction. */
    public:
        explicit Foreground ( const Window& window );
        ~Foreground ();
    };

} }

#endif /* _w32_gdi_Foreground_hpp__ */
