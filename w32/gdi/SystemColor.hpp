#ifndef _w32_gdi_SystemColor_hpp__
#define _w32_gdi_SystemColor_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace gdi {

    class Color;

        /*!
         * @brief Enumeration of all colors named by the system.
         */
    class SystemColor
    {
        /* nested types. */
    public:
        typedef int Value;

        /* class data. */
    public:
        static const SystemColor activeBorder ();
        static const SystemColor activeCaption ();
        static const SystemColor applicationWorkspace ();
        static const SystemColor buttonFace ();
        static const SystemColor buttonHighlight ();
        static const SystemColor buttonShadow ();
        static const SystemColor buttonText ();
        static const SystemColor captionText ();
        static const SystemColor desktop ();
        static const SystemColor grayText ();
        static const SystemColor highlight ();
        static const SystemColor highlightText ();
        static const SystemColor hotlight ();
        static const SystemColor inactiveBorder ();
        static const SystemColor inactiveCaption ();
        static const SystemColor inactiveCaptionText ();
        static const SystemColor tooltipBackground ();
        static const SystemColor tooltipText ();
        static const SystemColor menu ();
        static const SystemColor menuText ();
        static const SystemColor scrollbar ();
        static const SystemColor window ();
        static const SystemColor windowFrame ();
        static const SystemColor windowText ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        SystemColor ( Value value );

        /* operators. */
    public:
            /*!
             * @brief Obtains the system color's identifier.
             */
        operator Value () const;

            /*!
             * @brief Obtains the current RGB value of a system color.
             */
        operator Color () const;
  };

} }

#endif /* _w32_gdi_SystemColor_hpp__ */
