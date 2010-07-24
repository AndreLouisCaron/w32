#ifndef _w32_gdi_Key_hpp__
#define _w32_gdi_Key_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

    class KeyboardNotification;

    class W32_GDI_EXPORT Key
    {
        // Need to parse keycode from keyboard notification.
    friend class KeyboardNotification;

        /* class data. */
    public:
        static const Key shift ();
        static const Key lshift ();
        static const Key rshift ();
        static const Key control ();
        static const Key lcontrol ();
        static const Key rcontrol ();
        static const Key menu ();
        static const Key lmenu ();
        static const Key rmenu ();

        /* data. */
    private:
        int myIdentifier;

        /* construction. */
    private:
        Key ( int identifier );

        /* class methods. */
    public:
        static bool up ( const Key& key );
        static bool down ( const Key& key );
        static bool toggled ( const Key& key );

        /* methods. */
    public:
        int identifier () const;
    };

} }

#endif /* _w32_gdi_Key_hpp__ */
