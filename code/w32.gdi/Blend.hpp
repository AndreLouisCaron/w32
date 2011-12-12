#ifndef _w32_gdi_Blend_hpp__
#define _w32_gdi_Blend_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
