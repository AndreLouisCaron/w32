#ifndef _win32c_gdi_TextMetrics_hpp__
#define _win32c_gdi_TextMetrics_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

// See GetTextMetrics(), GetTextExtentPoint32().

namespace w32 { namespace gdi {

    class DeviceContext;

        /*!
         * @brief Obtains information about the currently selected font.
         */
    class TextMetrics
    {
        /* nested types. */
    public:
        typedef ::TEXTMETRICW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Computes mesures using the current mapping mode.
             */
        TextMetrics ( const DeviceContext& device );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

            /*!
             * @brief Obtains the height of the font.
             */
        long height () const;
    };

} }


#endif /* _win32c_gdi_TextMetrics_hpp__ */
