#ifndef _w32_gdi_StatusBar_hpp__
#define _w32_gdi_StatusBar_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace gdi {

    class Rectangle;

        /*!
         * @brief Control used to display status messages.
         */
    class W32_GDI_EXPORT StatusBar :
        public Control
    {
        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated static control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit StatusBar ( const Handle& handle );

            /*!
             * @brief Creates a new static control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        StatusBar ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
        void caption ( const string& caption );
    };

} }

#endif /* _w32_gdi_StatusBar_hpp__ */
