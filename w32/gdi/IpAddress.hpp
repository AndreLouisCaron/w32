#ifndef _w32_gdi_IpAddress_hpp__
#define _w32_gdi_IpAddress_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Control used to enter an IP address.
         */
    class IpAddress :
        public Control
    {
        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated IP address editor.
             *
             * @see claim()
             * @see proxy()
             */
        explicit IpAddress ( const Handle& handle );

            /*!
             * @brief Creates a new IP address editor on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        IpAddress ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
    };

} }

#endif /* _w32_gdi_IpAddress_hpp__ */
