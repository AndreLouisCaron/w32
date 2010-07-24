#ifndef _w32_gdi_WindowSearch_HPP__
#define _w32_gdi_WindowSearch_HPP__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Window.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Wraps a search for top-level windows.
         */
    class WindowSearch
    {
        /* construction. */
    public:
            /*!
             * @brief Releases any acquired resources.
             */
        virtual ~WindowSearch () {
        }

        /* methods. */
    public:
            /*!
             * @brief Performs the search for all top-level windows.
             */
        void perform ();

            /*!
             * @brief User-defined hook to process search results.
             */
        virtual void result ( const Window& window ) = 0;
    };

} }

#endif /* _w32_gdi_WindowSearch_HPP__ */
