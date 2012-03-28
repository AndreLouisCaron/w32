/*!
 * @file convert-pnm-to-bmp32.cpp
 * @author Andre Caron
 *
 * @brief Converts a Portable aNy Map to a raw (agbr) windows bitmap file.
 */

#include "pnm-to-bmp32.hpp"
#include <fstream>
#include <iostream>

#include <w32/app/console-program.hpp>

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
        
        pnm::Header header;
        if ( !(input >> header) ) {
            std::cerr
                << "Input file \"" << argv[1] << "\" is not a Portable aNy Map."
                << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Save the image in Windows Bitmap format.
        convert(header,input).save(argv[2]);

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
