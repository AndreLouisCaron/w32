#ifndef _w32_gdi_Edit_hpp__
#define _w32_gdi_Edit_hpp__

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

    class W32_GDI_EXPORT Edit :
        public Control
    {
        /* nested types. */
    public:
        typedef Notification< Edit, EN_SETFOCUS > Focus;
        typedef Notification< Edit, EN_KILLFOCUS > Ignore;
        typedef Notification< Edit, EN_CHANGE > Change;
        typedef Notification< Edit, EN_UPDATE > Update;
        typedef Notification< Edit, EN_MAXTEXT > MaximumText;
        typedef Notification< Edit, EN_HSCROLL > HorizontalScroll;
        typedef Notification< Edit, EN_VSCROLL > VerticalScroll;

        /* construction. */
    public:
            /*!
             * @brief Creates a wrapper for a pre-allocated progress bar.
             *
             * @see claim()
             * @see proxy()
             */
        explicit Edit ( const Handle& handle );

            /*!
             * @brief Creates a new progress bar on @a window in @a bounds.
             *
             * @param window Parent window owning the control.
             * @param bounds Control bounds. Defines the maximum extent.
             */
        Edit ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief Change the obfuscating character.
             */
        void obfuscator ( wchar_t character );
    };

} }

#endif /* _w32_gdi_Edit_hpp__ */
