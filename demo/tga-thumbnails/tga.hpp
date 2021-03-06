#ifndef _tga_hpp__
#define _tga_hpp__

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

#include <w32.hpp>
#include <cstddef>
#include <iosfwd>
#include <iostream>
#include <sstream>

namespace tga
{
    using w32::byte;
    using w32::word;
    using w32::dword;

        /*!
         * @brief File header for an image in the Portable aNy Map (PNM) family.
         */
    class Header
    {
        byte myData[18];
    public:
        Header () {
            std::memset(myData, 0, sizeof(myData));
        }
        byte * data () {
            return (myData);
        }
        std::size_t size () const {
            return (18);
        }
    private:
        byte make_byte ( std::size_t offset ) const {
            return (myData[offset]);
        }
        word make_word ( std::size_t offset ) const {
            return (myData[offset] | (myData[offset+1]<<8));
        }
    public:
        std::size_t idlength () const {
            return (make_byte(0x00));
        }
            // 00: rgb, 1: indexed.
        std::size_t cmaptype () const {
            return (make_byte(0x01));
        }
            // 01: raw indexed,
            // 02: raw rgb,
            // 03: raw grayscale,
            // 09: rle indexed,
            // 10: rle rgb,
            // 11: rle grayscale.
            // 32: ?
            // 33: ?
        std::size_t encoding () const {
            return (make_byte(0x02));
        }
        std::size_t cmapoffset () const {
            return (make_word(0x03));
        }
        std::size_t cmaplength () const {
            return (make_word(0x05));
        }
        std::size_t cmapdepth () const {
            return (make_byte(0x07));
        }
        std::size_t xoffset () const {
            return (make_word(0x08));
        }
        std::size_t yoffset () const {
            return (make_word(0x0a));
        }
        std::size_t width () const {
            return (make_word(0x0c));
        }
        std::size_t height () const {
            return (make_word(0x0e));
        }
        std::size_t bitdepth () const {
            return (make_byte(0x10));
        }
        std::size_t imdescriptor () const {
            return (make_byte(0x11));
        }
        std::size_t depth () const {
            return (bitdepth()/8);
        }
        bool topdown () const {
            return ((imdescriptor()&0x20) != 0);
        }
    };

        /*!
         * @brief Fetch the header for an image in the PNM family.
         */
    inline std::istream& operator>> ( std::istream& input, Header& header )
    {
            // Read the entire header at once.
        input.read((char*)header.data(), header.size());

            // Ignore image identification for now.
        input.ignore(header.idlength());
        if ( header.cmaptype() == 1 )
        {
            std::cerr
                << "color map entries: " << header.cmaplength() << "."
                << std::endl;
            std::cerr
                << "color map 1st entry: " << header.cmapoffset() << "."
                << std::endl;
            std::cerr
                << "color map depth: " << header.cmapdepth() << "."
                << std::endl;
        }
        std::cerr
            << "image depth: " << header.depth() << "."
            << std::endl;

        return (input);
    }

    class Palette
    {
        const Header& myHeader;
        byte *const myEntries;
        Palette ( const Palette& );
        Palette& operator= ( const Palette& );
    public:
        Palette ( const Header& header )
            : myHeader(header),
              myEntries(new byte[size()])
        {}
        ~Palette () {
            delete [] myEntries;
        }
        byte * data () {
            return (myEntries);
        }
        std::size_t compressed_size () const {
            return (depth()*myHeader.cmaplength());
        }
        std::size_t size () const {
            return (4*myHeader.cmaplength());
        }
        std::size_t depth () const {
            return (myHeader.cmapdepth()/8);
        }
        std::size_t length () const {
            return (myHeader.cmaplength());
        }
        std::size_t offset () const {
            return (myHeader.cmapoffset());
        }
        const byte * operator() ( std::size_t i ) const {
            return (myEntries+4*(offset()+i));
        }
        friend std::istream& operator>>
            ( std::istream& input, Palette& palette );
        static void skip ( const Header& header, std::istream& input )
        {
                // Just ask the stream to skip so many bytes...
            const std::size_t depth = header.cmapdepth()/8;
            const std::size_t compressed_size = depth * header.cmaplength();
            input.ignore(compressed_size);
        }
    };

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

#endif /* _tga_hpp__ */
