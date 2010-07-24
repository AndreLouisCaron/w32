#ifndef _w32_gdi_Animation_hpp__
#define _w32_gdi_Animation_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Enumeration of show/hide animations for windows.
         */
    class W32_GDI_EXPORT Animation
    {
        /* class data. */
    public:
            /*!
             * @brief Shows the window by progressivly alpha-blending it.
             */
        static const Animation blend ();

            /*!
             * @brief Hides the window by progressivly alpha-blending it.
             */
        static const Animation fade ();

            /*!
             * @brief Hides the window by progressivly inflating it inwards.
             */
        static const Animation expand ();

            /*!
             * @brief Hides the window by progressivly shinking it inwards.
             */
        static const Animation collapse ();

        /* nested types. */
    public:
        typedef dword Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Animation ( Value value );

        /* methods. */
    public:
            /*!
             * @brief Obtains the animation's identifier.
             */
        Value value () const;
    };

} }

#endif /* _w32_gdi_Animation_hpp__ */
