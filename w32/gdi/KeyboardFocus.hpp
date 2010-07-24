#ifndef _win32c_gdi_KeyboardFocus_hpp__
#define _win32c_gdi_KeyboardFocus_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/NotCopyable.hpp>
#include <Windows.h>

namespace win32c { namespace gdi {

        /*!
         * @brief Allows temporary attribution of focus to a given window.
         *
         * The focus is returned to the window that previously had the focus
         * once this object passes out of scope. For permanent attribution of
         * window focus, see the \c Window::focus() function.
         */
    class KeyboardFocus :
        private NotCopyable
    {
        /* data. */
    private:
        ::HWNG myPredecessor;

        /* construction. */
    public:
        explicit KeyboardFocus ( Window& window );
        ~KeyboardFocus ();
    };

} }

#endif /* _win32c_gdi_KeyboardFocus_hpp__ */
