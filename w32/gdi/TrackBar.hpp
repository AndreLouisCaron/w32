#ifndef _w32_gdi_TrackBar_hpp__
#define _w32_gdi_TrackBar_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Control.hpp>

namespace w32 { namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Control for selecting a value in range.
         */
    class TrackBar :
        public Control
    {
        /* construction. */
    public:
        explicit TrackBar ( const Handle& handle );
        TrackBar ( Window& window, const Rectangle& bounds );

        /* methods. */
    public:
            /*!
             * @brief 
             */
        void clearTicks ( bool redraw = true );

            /*!
             * @brief 
             */
        Rectangle channelArea () const;

            /*!
             * @brief 
             */
        int tickCount () const;

            /*!
             * @brief 
             */
        int minimum () const;

            /*!
             * @brief 
             */
        void minimum ( int value, bool redraw = true );

            /*!
             * @brief 
             */
        int maximum () const;

            /*!
             * @brief 
             */
        void maximum ( int value, bool redraw = true );

            /*!
             * @brief 
             */
        int position () const;

            /*!
             * @brief 
             */
        void position ( int value, bool redraw = true );

            /*!
             * @brief 
             */
        void tickFrequency ( int frequency );

            /*!
             * @brief 
             */
        void clearSelectionRange ();

            /*!
             * @brief 
             */
        int selectionStart () const;

            /*!
             * @brief 
             */
        void selectionStart ( int value, bool redraw = true );

            /*!
             * @brief 
             */
        int selectionEnd () const;

            /*!
             * @brief 
             */
        void selectionEnd ( int value, bool redraw = true );

            /*!
             * @brief 
             */
        void selection ( int start, int end, bool redraw = true );
    };

} }

#endif /* _w32_gdi_TrackBar_hpp__ */
