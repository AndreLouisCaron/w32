#ifndef _pnm_hpp__
#define _pnm_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
