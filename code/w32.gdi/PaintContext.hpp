#ifndef _w32_gdi_PaintContext_hpp__
#define _w32_gdi_PaintContext_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.gdi/DeviceContext.hpp>

namespace w32{ namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Wraps the context used during drawing operations.
         */
    class PaintContext :
        private NotCopyable
    {
        /* nested types. */
    private:
        typedef ::PAINTSTRUCT Data;

        /* data. */
    private:
        Data myData;
        DeviceContext myDevice;

        /* construction. */
    public:
        explicit PaintContext ( Window& window );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        DeviceContext device () const;

            /*!
             * @brief Ask if you should redraw the window's background.
             */
        bool erase () const;

            /*!
             * @brief Query what area we should redraw.
             */
        Rectangle area () const;
    };

} }

#endif /* _w32_gdi_PaintContext_hpp__ */
