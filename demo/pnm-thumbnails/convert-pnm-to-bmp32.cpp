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
