#ifndef _w32_gdi_Calendar_hpp__
#define _w32_gdi_Calendar_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.gdi/Control.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Calendar, showing one month at a time and allowing a user to
         *   pick a date.
         */
    class Calendar :
        public Control
    {
        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated calendar control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Calendar ( const Handle& handle );

            /*!
             * @brief Creates a new calendar control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        Calendar ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
    };

} }

#endif /* _w32_gdi_Calendar_hpp__ */
