#ifndef _win32c_gdi_PropertySearch_hpp__
#define _win32c_gdi_PropertySearch_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../NotCopyable.hpp"
#include <Windows.h>

namespace win32c { namespace gdi {

        /*!
         * @brief Finds all of a window's properties.
         */
    class PropertySearch
    {
        /* methods. */
    public:
            /*!
             * @brief Runs the enumeration for \c owner's properties.
             */
        void enumerate ( const Window& owner );

            /*!
             * @brief Called once for each property that is found.
             *
             * You may remove the property, but you may not remove other ones
             * or add any new ones. You should be careful about what yielding
             * control to other tasks.
             */
        virtual void result ( const char * name, void * value ) = 0;
    };

} }

#endif /* _win32c_gdi_PropertySearch_hpp__ */
