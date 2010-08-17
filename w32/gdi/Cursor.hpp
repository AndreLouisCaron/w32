#ifndef _w32_gdi_Cursor_hpp__
#define _w32_gdi_Cursor_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/NotCopyable.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Image displayed where the mouse currently points.
         */
    class W32_GDI_EXPORT Cursor
    {
        /* nested types. */
    public:
        typedef Reference< ::HCURSOR, void(*)(::HCURSOR) > Handle;

        class Show;
        class Hide;

        /* class methods. */
    public:
        static Handle claim ( ::HCURSOR object );
        static Handle proxy ( ::HCURSOR object );

        /* class data. */
    public:
        static const Cursor appstarting ();
        static const Cursor arrow ();
        static const Cursor cross ();
        static const Cursor hand ();
        static const Cursor no ();
        static const Cursor ibeam ();
        static const Cursor sizeall ();
        static const Cursor sizenesw ();
        static const Cursor sizens ();
        static const Cursor sizenwse ();
        static const Cursor sizewe ();
        static const Cursor up ();
        static const Cursor wait ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Cursor ( const Handle& handle );
        explicit Cursor ( const string& path );

        /* methods. */
    public:
            /*!
             * @brief Obtains the cursor's handle.
             */
        const Handle& handle () const;
    };

    class W32_GDI_EXPORT Cursor::Show :
        private NotCopyable
    {
        /* construction. */
    public:
        Show () {
            ::ShowCursor(TRUE);
        }

        ~Show () {
            ::ShowCursor(FALSE);
        }
    };

    class W32_GDI_EXPORT Hide :
        private NotCopyable
    {
        /* construction. */
    public:
        Hide () {
            ::ShowCursor(FALSE);
        }

        ~Hide () {
            ::ShowCursor(TRUE);
        }
    };

} }

#endif /* _w32_gdi_Cursor_hpp__ */
