// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "tga-to-bmp32.hpp"
#include <fstream>
#include <iostream>

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        if ( argc < 3 ) {
            std::cerr << "No input file!" << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Open the input file.
        std::ifstream input(argv[1],std::ios::binary);
        if ( !input.is_open() )
        {
            std::cerr
                << "Input file \"" << argv[1] << "\" could not be opened."
                << std::endl;
            return (EXIT_FAILURE);
        }
        
        tga::Header header;
        if ( !(input >> header) ) {
            std::cerr
                << "Input file \"" << argv[1] << "\" is not a Portable aNy Map."
                << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Save the image in Windows Bitmap format.
        tga::convert(header,input,w32::astring(argv[2]).data());
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.com.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.gdi.lib" )
#pragma comment ( lib, "w32.shl.lib" )
#pragma comment ( lib, "w32.shl.ext.lib" )
