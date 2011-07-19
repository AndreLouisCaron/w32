#ifndef _w32_gdi_Group_hpp__
#define _w32_gdi_Group_hpp__

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

        /*!
         * @brief Group of controls with a title, around which a border is set.
         */
    class Group :
        public Control
    {
        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated group control.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Group ( const Handle& handle );

            /*!
             * @brief Creates a new group control on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        Group ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Defines the group's title.
             */
        void title ( const string& title );

            /*!
             * @brief Obtains the group's title.
             */
        string title () const;
    };

} }

#endif /* _w32_gdi_Group_hpp__ */
