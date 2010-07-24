// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "tga.hpp"
#include "tga-to-bmp32.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace tga {

    void rle_rgb24
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
        byte * current = buffer;
        while ( current < buffer+3*pixelcount )
        {
                // Fetch run-length tag.
            const std::size_t tag = input.get();
            
                // Run-length encoding flags bits as such.
            if ( tag > 127 )
            {
                const std::size_t length = (tag - 127);
                byte pixel[3]; input.read((char*)pixel, 3);
                for ( std::size_t i = 0; (i < length); ++i ) {
                    (*current++) = pixel[0];
                    (*current++) = pixel[1];
                    (*current++) = pixel[2];
                }
            }
                // Other runs are read directly.
            else
            {
                const std::size_t length = 3 * (tag + 1);
                tga::read(input, current, length);
                current += length;
            }
        }
    }

    void rle_rgba16
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
        byte * current = buffer;
        while ( current < buffer+2*pixelcount )
        {
                // Fetch run-length tag.
            const std::size_t tag = input.get();
            
                // Run-length encoding flags bits as such.
            if ( tag > 127 )
            {
                const std::size_t length = (tag - 127);
                byte pixel[2]; input.read((char*)pixel, 2);
                for ( std::size_t i = 0; (i < length); ++i ) {
                    (*current++) = pixel[0];
                    (*current++) = pixel[1];
                }
            }
                // Other runs are read directly.
            else
            {
                const std::size_t length = 2 * (tag + 1);
                tga::read(input, current, length);
                current += length;
            }
        }
    }

    void rle_rgba32
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
        byte * current = buffer;
        while ( current < buffer+4*pixelcount )
        {
                // Fetch run-length tag.
            const std::size_t tag = input.get();
            
                // Run-length encoding flags bits as such.
            if ( tag > 127 )
            {
                const std::size_t length = (tag - 127);
                byte pixel[4]; input.read((char*)pixel, 4);
                for ( std::size_t i = 0; (i < length); ++i ) {
                    (*current++) = pixel[0];
                    (*current++) = pixel[1];
                    (*current++) = pixel[2];
                    (*current++) = pixel[3];
                }
            }
                // Other runs are read directly.
            else
            {
                const std::size_t length = 4 * (tag + 1);
                tga::read(input, current, length);
                current += length;
            }
        }
    }

    void rle_y8
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
            // load rle & decompress to indices.
        byte * current = buffer;
        while ( current < buffer+pixelcount )
        {
                // Fetch run-length tag.
            const std::size_t tag = input.get();
            
                // Run-length encoding flags bits as such.
            if ( tag > 127 )
            {
                std::size_t length = 1 * (tag - 127);
                const byte index = input.get();
                for ( std::size_t i = 0; (i < length); ++i ) {
                    (*current++) = index;
                }
            }
                // Other runs are read directly.
            else
            {
                const w32::int16 length = 1 * (tag + 1);
                tga::read(input, current, length);
                current += length;
            }
        }
    }

    void rle_i8
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
            // Decompress exactly like getting 8-bit pixels.
        rle_y8(input, buffer, pixelcount);
    }

    void rle_i16
        ( std::istream& input, byte * buffer, std::size_t pixelcount )
    {
            // Decompress exactly like getting 16-bit pixels.
        rle_rgba16(input, buffer, pixelcount);
    }

    void y8_to_rgba32 ( byte * buffer, std::size_t pixelcount )
    {
        byte * lhs = buffer + 4*pixelcount;
        byte * rhs = buffer + 1*pixelcount;
        while ( rhs > buffer ) {
            lhs -= 4, --rhs;
            lhs[2] = lhs[1] = lhs[0] = rhs[0], lhs[3] = 0xff;
        }
    }

    void rgba16_to_rgba32 ( byte * buffer, std::size_t pixelcount )
    {
        byte * lhs = buffer + 4*pixelcount;
        byte * rhs = buffer + 2*pixelcount;
        while ( rhs > buffer )
        {
            lhs -= 4, rhs -= 2;
            
                // Extract each channel.
            lhs[1] = ((rhs[0] & 0xf8) >> 3);
            lhs[0] =
                ((rhs[0] & 0x07) << 2) | ((rhs[1] & 0xfb) >> 6);
            lhs[2] = ((rhs[1] & 0x3e) >> 1);
            lhs[3] = (rhs[1] & 0x01);
            
                // Rescale to 8 bits per component.
            lhs[0] = (lhs[0] << 3) | (lhs[0] >> 2);
            lhs[1] = (lhs[1] << 3) | (lhs[1] >> 2);
            lhs[2] = (lhs[2] << 3) | (lhs[2] >> 2);
            lhs[3] = (lhs[3] * 0xff);
        }
    }

    void rgb24_to_rgba32 ( byte * buffer, std::size_t pixelcount )
    {
        byte * lhs = buffer + 4*pixelcount;
        byte * rhs = buffer + 3*pixelcount;
        while ( rhs > buffer ) {
            lhs -= 4, rhs -= 3;
            lhs[0] = rhs[0];
            lhs[1] = rhs[1];
            lhs[2] = rhs[2];
            lhs[3] = 0xff;
        }
    }

    void i8_to_rgba32
        ( byte * buffer, std::size_t pixelcount, const Palette& palette )
    {
        std::cerr<< "Un-mapping using color palette." << std::endl;
        byte * lhs = buffer + 4*pixelcount;
        byte * rhs = buffer + 1*pixelcount;
        while ( rhs > buffer ) {
            lhs -= 4, --rhs;
            const byte * entry = palette(*rhs);
            std::copy(entry, entry+4, lhs);
        }
    }

    void bottomup_to_topdown
        ( byte * buffer, std::size_t width, std::size_t height )
    {
        byte * lhs = buffer;
        byte * rhs = buffer + 4*width*height;
        while ( lhs < rhs )
        {
                // Seek back to beginning of the line.
            rhs -= 4*width;
            
                // Swap entire scan line...
            std::swap_ranges(lhs, lhs+4*width, rhs);
            
                // Move to next line.
            lhs += 4 * width;
        }
    }

    std::istream& operator>>
        ( std::istream& input, Palette& palette )
    {
        std::cerr
            << "Requesting " << palette.compressed_size()
            << " bytes of palette." << std::endl;
        input.read((char*)palette.data(), palette.compressed_size());
        std::cerr
            << "    ...obtained " << input.gcount() << "!" << std::endl;
        if ( palette.depth() == 2 ) {
            std::cerr << "Reading 16-bit color palette." << std::endl;
            rgba16_to_rgba32(palette.data(), palette.length());
        }
        else if ( palette.depth() == 3 ) {
            std::cerr << "Reading 24-bit color palette." << std::endl;
            rgb24_to_rgba32(palette.data(), palette.length());
        }
        return (input);
    }

    w32::gdi::Image convert
        ( const tga::Header& header, std::istream& input )
    {
            // Create a device independant bitmap fitted for the screen.
        w32::gdi::Size size(header.width(), header.height());
        w32::gdi::Image source(size, 32);
        
            // Load the source image from the file, into the bitmap.
        { w32::gdi::DeviceIndependantBitmap::Guard guard(source);
            
            w32::uint8 *const buffer =
                static_cast<w32::uint8*>(source.buffer());
            const std::size_t pixelcount = header.width()*header.height();
            
                // raw indexed.
            if ( header.encoding() == 1 )
            {
                std::cerr << "Encoding 1." << std::endl;
                
                    // load palette.
                Palette palette(header); input >> palette;
                
                    // load indices.
                tga::read(input,buffer,header.depth()*pixelcount);
                
                    // Map I to (A)GBR (inplace)!
                i8_to_rgba32(buffer, pixelcount, palette);
            }
                // raw rgb.
            else if ( header.encoding() == 2 )
            {
                std::cerr << "Encoding 2." << std::endl;
                
                    // Skip the palette, if any.
                Palette::skip(header, input);
                
                    // Load raw data.
                tga::read(input, buffer, header.depth()*pixelcount);
                
                    // Map RGB to (A)GBR (inplace)!
                if ( header.depth() == 2 ) {
                    rgba16_to_rgba32(buffer, pixelcount);
                }
                else if ( header.depth() == 3 ) {
                    rgb24_to_rgba32(buffer, pixelcount);
                }
            }
                // raw grayscale.
            else if ( header.encoding() == 3 )
            {
                std::cerr << "Encoding 3." << std::endl;
                
                    // Skip the palette, if any.
                Palette::skip(header, input);
                
                    // Load raw data.
                tga::read(input,buffer,1*pixelcount);
                
                    // Map Y to (A)GBR (inplace)!
                y8_to_rgba32(buffer, pixelcount);
            }
                // rle indexed.
            else if ( header.encoding() == 9 )
            {
                std::cerr << "Encoding 9." << std::endl;
                
                    // load palette.
                Palette palette(header); input >> palette;
                
                    // load rle & decompress to indices.
                if ( header.depth() == 1 ) {
                    rle_i8(input, buffer, pixelcount);
                }
                else {
                    rle_i16(input, buffer, pixelcount);
                }
                
                    // Map I to (A)BGR (inplace)!
                i8_to_rgba32(buffer, pixelcount, palette);
            }
                // rle rgb(a).
            else if ( header.encoding() == 10 )
            {
                std::cerr << "Encoding 10." << std::endl;
                
                    // Skip the palette, if any.
                Palette::skip(header, input);
                
                    // load rle & decompress to pixels.
                if ( header.depth() == 2 ) {
                    rle_rgba16(input, buffer, pixelcount);
                }
                if ( header.depth() == 3 ) {
                    rle_rgb24(input, buffer, pixelcount);
                }
                else if ( header.depth() == 4 ) {
                    rle_rgba32(input, buffer, pixelcount);
                }
                
                    // Map BGR to (A)BGR (inplace)!
                if ( header.depth() == 2 ) {
                    rgba16_to_rgba32(buffer, pixelcount);
                }
                else if ( header.depth() == 3 ) {
                    rgb24_to_rgba32(buffer, pixelcount);
                }
            }
                // rle grayscale.
            else if ( header.encoding() == 11 )
            {
                std::cerr << "Encoding 11." << std::endl;
                
                    // Skip the palette, if any.
                Palette::skip(header, input);
                
                    // load rle & decompress to raw.
                rle_y8(input, buffer, pixelcount);
                
                    // Map Y to (A)BGR (inplace)!
                y8_to_rgba32(buffer, pixelcount);
            }
            
               // Some images are bottom-up.
            if ( !header.topdown() ) {
                bottomup_to_topdown(buffer, header.width(), header.height());
            }
        }
        
        return (source);
    }

    void convert ( const tga::Header& header, std::istream& input, const char * output )
    {
        convert(header, input).save(output);
    }

}
