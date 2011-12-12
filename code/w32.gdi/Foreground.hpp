#ifndef _w32_gdi_Foreground_hpp__
#define _w32_gdi_Foreground_hpp__

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.gdi/Window.hpp>

namespace w32 { namespace gdi {

    void foreground ( const Window& window );
    Window foreground ();

    class Foreground :
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
