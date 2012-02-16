#ifndef _w32_gdi_DeviceCompatibleBitmap_hpp__
#define _w32_gdi_DeviceCompatibleBitmap_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32.gdi/Bitmap.hpp>

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
