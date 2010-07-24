#ifndef _tga_to_bmp32_hpp__
#define _tga_to_bmp32_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "tga.hpp"
#include <w32.hpp>
#include <w32.gdi.hpp>
#include <iosfwd>

namespace tga {

    w32::gdi::Image convert
        ( const tga::Header& header, std::istream& input );

    void convert
        ( const tga::Header& header, std::istream& input, const char * output );

}

#endif /* _tga_to_bmp32_hpp__ */
