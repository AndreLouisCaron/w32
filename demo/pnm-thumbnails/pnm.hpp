#ifndef _pnm_hpp__
#define _pnm_hpp__

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

#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <sstream>

namespace pnm
{
        /*!
         * @brief File header for an image in the Portable aNy Map (PNM) family.
         */
    struct Header
    {
        char magicnumber[3];
        std::size_t depth;
        std::size_t width;
        std::size_t height;
        std::stringstream comments;

        Header ()
            : depth(0), width(0), height(0)
        {
            magicnumber[0] = magicnumber[1] = magicnumber[2] = '\0';
        }
    };

        /*!
         * @brief Fetch the header for an image in the PNM family.
         */
    inline std::istream& operator>> ( std::istream& in, Header& header )
    {
        in.read(header.magicnumber,2); header.magicnumber[2] = '\0';
        header.comments.str("");
        for ( std::string comment; ((in >> std::ws) && (in.peek() == '#')); ) {
            in.ignore(1); in >> std::ws;
            std::getline(in,comment);
            header.comments << comment << std::endl;
        }
        in >> header.width >> header.height;
        const int type = int(header.magicnumber[1]-'0');
        if ((type == 2) || (type == 3) || (type == 5) || (type == 6)) {
            in >> header.depth;
        }
        else if ((type == 1) || (type == 4)) {
            header.depth = 1;
        }
        else {
            in.setstate(std::ios::failbit);
        }
        in.ignore(1);
        return (in);
    }

        /*!
         * @brief Reliably reads \c count bytes from an input stream.
         */
    inline std::istream& read (
        std::istream& input, unsigned char * bytes, std::streamsize count
        )
    {
        std::streamsize offset = 0;
        do {
            input.read(reinterpret_cast<char*>(bytes+offset),count-offset);
        } while ( input.good() && (offset += input.gcount()) < count );
        return (input);
    }

}

#endif /* _pnm_hpp__ */
