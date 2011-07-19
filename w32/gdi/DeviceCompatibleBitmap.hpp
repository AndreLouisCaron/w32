#ifndef _w32_gdi_DeviceCompatibleBitmap_hpp__
#define _w32_gdi_DeviceCompatibleBitmap_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/gdi/Bitmap.hpp>

namespace w32 { namespace gdi {

    class DeviceContext;
    class Size;

        /*!
         * @brief Wraps a bitmap that has the same format as a given device.
         *
         * This kind of bitmap is extremely useful when you need to do
         * fast copies of bitmaps onto screens. These are fast since the
         * system doesn't need to perform any conversions.
         */
    class DeviceCompatibleBitmap :
        public Bitmap
    {
        /* construction. */
    public:
            /*!
            * @brief Creates a bitmap suited for a particular device.
            *
            * @note Although this bitmap should be manipulated through a
            * compatible device context, it should be created using a real
            * device context or the system will allocate a monochrome bitmap.
             */
        DeviceCompatibleBitmap (
            const DeviceContext& context, const Size& size
            );
    };

} }

#endif /* _w32_gdi_DeviceCompatibleBitmap_hpp__ */
