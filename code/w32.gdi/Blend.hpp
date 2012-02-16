#ifndef _w32_gdi_Blend_hpp__
#define _w32_gdi_Blend_hpp__

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
#include <w32/types.hpp>
#include <w32.gdi/Color.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Base class for transparent window blending modes.
         */
    class Blend
    {
        /* nested types. */
    public:
        typedef ::BLENDFUNCTION Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Blend () {
            ::ZeroMemory(&myData, sizeof(myData));
        }

    protected:
        Blend ( byte source, byte format )
        {
            myData.BlendOp             = AC_SRC_OVER;
            myData.BlendFlags          = 0;
            myData.SourceConstantAlpha = source;
            myData.AlphaFormat         = format;
        }

        /* methods. */
    public:
            /*!
             * @brief Obtains the blend function's native description.
             */
        const Data& data () const {
            return (myData);
        }
    };

        /*!
         * @brief Blending function using a specific color as transparent.
         */
    class ColorKeyBlend : public Blend
    {
        /* data. */
    private:
        Color myKey;

        /* construction. */
    public:
        ColorKeyBlend ( Color key )
            : Blend(255,0), myKey(key)
        {}

        /* methods. */
    public:
            /*!
             * @brief Obtains the color key used to represent transparency.
             */
        Color key () const {
            return (myKey);
        }
    };

        /*!
         * @brief Blending function using a uniform opacity.
         */
    class UniformBlend : public Blend
    {
        /* construction. */
    public:
        UniformBlend ( byte opacity )
            : Blend(opacity, 0)
        {}

        /* methods. */
    public:
            /*!
             * @brief Obtains the opacity level.
             */
        byte opacity () const {
            return (data().SourceConstantAlpha);
        }
    };

        /*!
         * @brief Blending function using an alpha channel.
         */
    class PerPixelBlend : public Blend
    {
        /* construction. */
    public:
        PerPixelBlend ()
            : Blend(255, AC_SRC_ALPHA)
        {}
    };

} }

#endif /* _w32_gdi_Blend_hpp__ */
