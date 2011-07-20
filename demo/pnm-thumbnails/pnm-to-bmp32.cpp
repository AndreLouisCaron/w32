/*!
 * @file pnm-to-bmp32.cpp
 * @author Andre Caron
 *
 * @brief Converts a Portable aNy Map to a raw (agbr) windows bitmap file.
 */

#include "pnm.hpp"
#include "pnm-to-bmp32.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

namespace pnm {

    w32::gdi::Image convert
        ( const pnm::Header& header, std::istream& input )
    {
            // Create a device independant bitmap fitted for the screen.
        const w32::gdi::Size size(header.width,header.height);
        w32::gdi::Image source(size, 32);

            // Load the source image from the file, into the bitmap.
        { w32::gdi::DeviceIndependantBitmap::Guard guard(source);

            w32::uint8 *const buffer =
                static_cast<w32::uint8*>(source.buffer());
            const std::size_t pixelcount = size.width()*size.height();

            if ( std::strcmp(header.magicnumber,"P1") == 0 )
            {
                    // Map 0/1 to (A)GBR!
                w32::uint8 *const end = buffer + 4*pixelcount;
                w32::uint8 * lhs = buffer;
                for ( int y = 0; (lhs < end); lhs += 4 )
                {
                    if ( !(input >> y) ) {
                        // error...
                    }
                    lhs[3] = 0xff;
                    lhs[0] = lhs[1] = lhs[2] = w32::uint8((1-(y&0x1))*0xff);
                }
            }
            else if ( std::strcmp(header.magicnumber,"P2") == 0 )
            {
                    // Map Y to (A)GBR!
                w32::uint8 *const end = buffer + 4*pixelcount;
                w32::uint8 * lhs = buffer;
                for ( int y = 0; (lhs < end); lhs += 4 )
                {
                    if ( !(input >> y) ) {
                        // error.
                    }
                    lhs[3] = 0xff;
                    lhs[0] = lhs[1] = lhs[2] = w32::uint8(y&0xff);
                }
            }
            else if ( std::strcmp(header.magicnumber,"P3") == 0 )
            {
                    // Map Y to (A)GBR!
                w32::uint8 *const end = buffer + 4*pixelcount;
                w32::uint8 * lhs = buffer;
                for ( int r,g,b; (lhs < end); lhs +=4 )
                {
                    if ( !(input >> r >> g >> b) ) {
                        // error...
                    }
                    lhs[3] = 0xff;
                    lhs[2] = r;
                    lhs[1] = g;
                    lhs[0] = b;
                }
            }
            else if ( std::strcmp(header.magicnumber,"P4") == 0 )
            {
                const std::size_t orphans = header.width%8;
                const std::size_t unused = 8 - orphans;
                const std::size_t stride = (orphans > 0)?
                    ((header.width/8)+1) : (header.width/8);

                    // Read all the data, in packed form.
                if ( !pnm::read(input,buffer,stride*header.height) ) {
                    // error..
                }

                    // Map 0/1 bits to (A)GBR (inplace)!
                w32::uint8 * lhs = buffer + 4*pixelcount;
                w32::uint8 * rhs = buffer + stride*header.height;
                for ( std::size_t row= 0; (row < header.height); ++row )
                {
                        // Process the last byte carefully, if uneven.
                    if ( orphans > 0 )
                    {
                        --rhs;
                        rhs[0] >>= unused;
                        for ( std::size_t i = 0; (i < orphans); ++i ) {
                            lhs -= 4;
                            lhs[3] = 0xff;
                            lhs[2] = (1-((*rhs)&0x01))*0xff;
                            lhs[1] = lhs[2];
                            lhs[0] = lhs[1];
                            (*rhs) >>= 1;
                        }
                    }

                        // Process all other bytes normally.
                    for ( std::size_t j = 0; (j < header.width/8); ++j )
                    {
                        --rhs;
                        for ( std::size_t i = 0; (i < 8); ++i ) {
                            lhs -= 4;
                            lhs[3] = 0xff;
                            lhs[2] = (1-((*rhs)&0x01))*0xff;
                            lhs[1] = lhs[2];
                            lhs[0] = lhs[1];
                            (*rhs) >>= 1;
                        }
                    }
                }
            }
            else if ( std::strcmp(header.magicnumber,"P5") == 0 )
            {
                pnm::read(input,buffer,1*pixelcount);

                    // Map Y to (A)GBR (inplace)!
                w32::uint8 * lhs = buffer + 4*pixelcount;
                w32::uint8 * rhs = buffer + 1*pixelcount;
                while ( rhs > buffer ) {
                    lhs -= 4, --rhs;
                    lhs[3] = 0xff;
                    lhs[0] = lhs[1] = lhs[2] = rhs[0];
                }
            }
            else if ( std::strcmp(header.magicnumber,"P6") == 0 )
            {
                pnm::read(input,buffer,3*pixelcount);

                    // Map RGB to (A)GBR (inplace)!
                w32::uint8 * lhs = buffer + 4*pixelcount;
                w32::uint8 * rhs = buffer + 3*pixelcount;
                while ( rhs > buffer ) {
                    lhs -= 4, rhs -= 3;
                    lhs[3] = 0xff;
                    lhs[2] = rhs[0];
                    lhs[1] = rhs[1];
                    lhs[0] = rhs[2];
                }
            }
        }
        return (source);
    }

    void convert ( const pnm::Header& header, std::istream& input, const char * output )
    {
        convert(header, input).save(output);
    }

}
