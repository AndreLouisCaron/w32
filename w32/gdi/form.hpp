#ifndef _w32_gdi_form_hpp__
#define _w32_gdi_form_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/w32.hpp>
#include <w32/gdi.hpp>

namespace {

        /*!
         * @brief Holder for "global" variables in your application.
         *
         * This typically registers the window class for applications with a
         * main desktop window. It may also hold any other "global" variables
         * that may throw exceptions upon initialization.
         */
    class Application;

        /*!
         * @brief Holer for your application's main desktop window.
         *
         * This class typically holds all window and control resources.
         */
    class Form;

        /*!
         * @brief Handles each event loop in the application.
         */
    void process (
        w32::gdi::EventQueue& queue, const w32::gdi::Event& event
        );

}

#endif /* _w32_gdi_form_hpp__ */
