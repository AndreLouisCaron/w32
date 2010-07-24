#ifndef _w32_gdi_Window_hpp__
#define _w32_gdi_Window_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>
#include <w32/gdi/Animation.hpp>
#include <w32/gdi/Class.hpp>
#include <w32/gdi/Color.hpp>
#include <w32/gdi/Event.hpp>
#include <w32/gdi/Icon.hpp>
#include <w32/gdi/Font.hpp>
#include <w32/gdi/Rectangle.hpp>
#include <w32/gdi/Region.hpp>
#include <os.hpp>

namespace w32 { namespace gdi {

    class Brush;

        /*!
         * @brief Wraps a window resource.
         */
    class W32_GDI_EXPORT Window
    {
        /* nested types. */
    public:
            /*!
             * @brief Wraps access to the window's native handle.
             */
        typedef Reference< ::HWND, void(*)(::HWND) > Handle;

        class Style;

            /*!
             */
        typedef ::LRESULT ( __stdcall * Callback )
            ( ::HWND, ::UINT, ::WPARAM, ::LPARAM );

            // Sleek callback adapter.

        template<typename H> static ::LRESULT __stdcall adapt
            ( ::HWND hwnd, uint msg, wparam wp, lparam lp );

        template<typename T>
        class Handler;

        /* class methods. */
    public:
        static Handle claim ( ::HWND object );
        static Handle proxy ( ::HWND object );

            /*!
             * @brief Adjusts a client area's bounds to the whole window.
             *
             * When creating a window, you normally request a certain client
             * area. This function adjusts that rectangle such that it includes
             * the entire window's area.
             */
        static Rectangle adjust (
            const Rectangle& bounds, const Style& style
            );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Window ( const Handle& handle );

        Window (
            const Registration& class_, const Rectangle& bounds
            );

        Window (
            const Registration& class_,
            const Rectangle& bounds, const Style& style
            );

        Window ( const Rectangle& bounds, const Style& style );

        /* methods. */
    public:
            /*!
             * @brief Obtains the window's handle.
             */
        const Handle& handle () const;

            /*!
             * @brief Request the window to redraw its entire client area.
             *
             * The system keeps track of what part of the window is invalidated
             * and sends a 'paint' message to the window when it is done
             * processing ALL of its other events.
             *
             * @see update()
             */
        void invalidate ();

            /*!
             * @brief Request the window to redraw part of its client area.
             *
             * The system keeps track of what part of the window is invalidated
             * and sends a 'paint' message to the window when it is done
             * processing ALL of its other events.
             *
             * @see update()
             */
        void invalidate ( const Rectangle& area );

            /*!
             * @brief Force drawing of invalidated area early.
             *
             * This forces sending a 'paint' message to the window (it its
             * invalidated area is not empty) even if the window still has
             * some messages to process.
             *
             * Use this sparingly because 
             */
        void update ();

            /*!
             * @brief Make the window appear, if it isn't.
             */
        void show ();

            /*!
             * @brief Make the window appear, using an animation.
             */
        void show ( const Animation& animation );

            /*!
             * @brief Make the window dissapear.
             */
        void hide ();

            /*!
             * @brief Make the window dissapear, using an animation.
             */
        void hide ( const Animation& animation );

            /*!
             * @brief Allows the window to receive input messages.
             */
        void enable ();

            /*!
             * @brief Prevents the window from receiving input messages.
             */
        void disable ();

            /*!
             * @brief Minimizes (iconifies) the window.
             */
        void minimize ();

            /*!
             * @brief Maximizes the window.
             */
        void maximize ();

            /*!
             * @brief Restores (un-iconifies) the minimized window.
             */
        void restore ();

            /*!
             * @brief Changes the window's parent-relative bounding rectangle.
             */
        void bounds ( const Rectangle& area );

            /*!
             * @brief Obtain the window's parent-relative bounding rectangle.
             */
        const Rectangle bounds () const;

            /*!
             * @brief Obtain the window's client area.
             */
        const Rectangle area () const;

            /*!
             * @brief Defines a new region for the window.
             */
        void region ( const Region& region );

            /*!
             * @brief Determines if the window is maximized or not.
             */
        bool minimized () const;

            /*!
             * @brief Determines if the window is minimized or not.
             */
        bool maximized () const;

            /*!
             * @brief Changed the user data, if you requested it.
             *
             * User data is requested when registering the window class for the
             * window. Make sure at least \code sizeof(void*) \endcode bytes are
             * requested.
             */
        void extra ( void * pointer );

            /*!
             * @brief Obtains the user data, if you requested it.
             *
             * User data is requested when registering the window class for the
             * window. Make sure at least \code sizeof(void*) \endcode bytes are
             * requested.
             */
        void * extra () const;

            /*!
             * @brief Forces the window to take focus.
             */
        void focus ();

        void font ( const Font& font );
        Font font () const;

        void background ( const Brush& brush );

        Icon bigicon () const;
        Icon smallicon () const;

        void icon ( const Icon& icon );

        void text ( const string& text );

            /*!
             * @brief Obtains the current window procedure.
             * @return Function pointer currently used as the window procedure.
             */
        Callback callback () const;

            /*!
             * @brief Changes the window procedure.
             * @return Function pointer previously used as the window procedure.
             * @post <code>this->callback() == callback</code>
             */
        Callback callback ( Callback callback );

        Style style () const;
        void style ( const Style& style );

        /*!
         * @brief Sets an event Handler for the window.
         *
         * @note This effectively overrides the window's extra memory @e and
         *   window procedure.
         * @post <code>extra() == &handler</code>
         * @post <code>callback() == &adapt<T></code>
         */
        template<typename T>
        void handler ( T& handler )
        {
                // Reference the event handler in the window's extra memory and
                // use the event handler adapter to generate a window procedure.
            extra(&handler), callback(&adapt<T>);
        }
    };

        /*!
         * @brief Configurator for window styles.
         */
    class W32_GDI_EXPORT Window::Style
    {
        /* data. */
    private:
        ::DWORD myStandard;
        ::DWORD myExtended;

        /* construction. */
    public:
        Style ();
        Style ( dword standard, dword extended )
            : myStandard(standard),
              myExtended(extended)
        {
        }

        /* methods. */
    public:
        const ::DWORD& standard () const {
            return (myStandard);
        }

        const ::DWORD& extended () const {
            return (myExtended);
        }

        Style& operator&= ( const Style& rhs )
        {
            myStandard &= rhs.myStandard;
            myExtended &= rhs.myExtended;
            return (*this);
        }

        Style& operator|= ( const Style& rhs )
        {
            myStandard |= rhs.myStandard;
            myExtended |= rhs.myExtended;
            return (*this);
        }

        void bordered () {
            myStandard |= WS_BORDER;
        }

        void captioned () {
            myStandard |= WS_CAPTION;
        }

        void child ()
        {
            myStandard &= ~WS_POPUP;
            myStandard |= WS_CHILD;
            #if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000)
                myExtended &= ~WS_EX_LAYERED;
            #endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000) */
        }

        void clipChildren ()
        {
            child();
            myStandard |= WS_CLIPCHILDREN;
        }

        void clipSiblings ()
        {
            child();
            myStandard |= WS_CLIPSIBLINGS;
        }

        void disabled ()
        {
            child();
            myStandard |= WS_DISABLED;
        }

        void dialogFrame () {
            myStandard |= WS_DLGFRAME;
        }

        void group () {
            myStandard |= WS_GROUP;
        }

        void horizontalScroll () {
            myStandard |= WS_HSCROLL;
        }

        void iconic () {
            myStandard |= WS_ICONIC;
        }

        void maximized () {
            myStandard |= WS_MAXIMIZE;
        }

        void maximizable () {
            systemMenu();
            myStandard |= WS_MAXIMIZEBOX;
        }

        void minimized () {
            myStandard |= WS_MINIMIZE;
        }

        void minimizable () {
            systemMenu();
            myStandard |= WS_MINIMIZEBOX;
        }

        void overlapped () {
            myStandard |= WS_OVERLAPPED;
        }

        Style& overlappedWindow () {
            myStandard |= WS_OVERLAPPEDWINDOW;
            return (*this);
        }

        Style& popup () {
            myStandard &= ~WS_CHILD;
            myStandard |= WS_POPUP;
            return (*this);
        }

        static Style popupWindow () {
            return (Style(WS_POPUPWINDOW,0));
        }

        void userSizable () {
            myStandard |= WS_SIZEBOX;
        }

        void systemMenu () {
            captioned();
            myStandard |= WS_SYSMENU;
        }

        void tabStop () {
            myStandard |= WS_TABSTOP;
        }

        void visible () {
            myStandard |= WS_VISIBLE;
        }

        void verticalScroll () {
            myStandard |= WS_VSCROLL;
        }

        void acceptFiles () {
            myExtended |= WS_EX_ACCEPTFILES;
        }

        void applicationWindow () {
            myExtended |= WS_EX_APPWINDOW;
        }

        void sunkenEdge () {
            myExtended |= WS_EX_CLIENTEDGE;
        }

        void contextHelp () {
            myExtended |= WS_EX_CONTEXTHELP;
        }

        void controlParent () {
            myExtended |= WS_EX_CONTROLPARENT;
        }

        void dialogModalFrame () {
            myExtended |= WS_EX_DLGMODALFRAME;
        }

        void left () {
            myExtended |= WS_EX_LEFT;
        }

        void leftVerticalScroll () {
            verticalScroll();
            myExtended |= WS_EX_LEFTSCROLLBAR;
        }

        void leftToRightReading () {
            myExtended |= WS_EX_LTRREADING;
        }

        void mdiChild () {
            myExtended |= WS_EX_MDICHILD;
        }

        void noParentNotify () {
            myExtended |= WS_EX_NOPARENTNOTIFY;
        }

        void extendedOverlappedWindow () {
            myExtended |= WS_EX_OVERLAPPEDWINDOW;
        }

        void paletteWindow () {
            myExtended |= WS_EX_PALETTEWINDOW;
        }

        void right () {
            myExtended |= WS_EX_RIGHT;
        }

        void rightVerticalScroll () {
            verticalScroll();
            myExtended |= WS_EX_RIGHTSCROLLBAR;
        }

        void rightToLeftReading () {
            verticalScroll();
            myExtended |= WS_EX_RIGHTSCROLLBAR;
        }

        void staticEdge () {
            verticalScroll();
            myExtended |= WS_EX_RIGHTSCROLLBAR;
        }

        void toolWindow () {
            myExtended |= WS_EX_TOOLWINDOW;
        }

        void topmost () {
            myExtended |= WS_EX_TOPMOST;
        }

        void transparent () {
            myExtended |= WS_EX_TRANSPARENT;
        }

        void windowEdge () {
            myExtended |= WS_EX_WINDOWEDGE;
        }

        #if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000)
            void layered () {
                myExtended |= WS_EX_LAYERED;
            }
        #endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_2000) */

        #if (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XP)
            void composited () {
                myExtended |= WS_EX_COMPOSITED;
            }
        #endif /* (MICROSOFT_WINDOWS >= MICROSOFT_WINDOWS_XP) */
    };

} }

#endif /* _w32_gdi_Window_hpp__ */
