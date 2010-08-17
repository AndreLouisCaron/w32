#ifndef _w32_gdi_image_hpp__
#define _w32_gdi_image_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/gdi/DeviceIndependantBitmap.hpp>

namespace w32 { namespace gdi {

    typedef w32::gdi::DeviceIndependantBitmap Image;

        /*!
         * @brief Loads an image from an input file.
         */
    W32_GDI_EXPORT Image image ( const string& path );

        /*!
         * @brief Saves an image to an output file.
         */
    W32_GDI_EXPORT void image ( const Image& image, const string& path );

} }

#endif /* _w32_gdi_image_hpp__ */
