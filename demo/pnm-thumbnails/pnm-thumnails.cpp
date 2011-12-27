// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "pnm.hpp"
#include "pnm-to-bmp32.hpp"
#include <w32.shl.hpp>
#include <w32.shl.ext.hpp>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <cstring>

namespace {

        /*!
         * @brief Implements the thumbnail provider for PNM images.
         *
         * This is the hook our system invokes to query for the thumbnail!
         */
    class Extension :
        public w32::shl::ext::ThumbnailProvider // (vista)
        //public w32::shl::ext::ThumbnailHandler // (xp)
    {
        /* nested types. */
    public:
        class InvalidPnmFile {};

        /* class data. */
    public:
        static const w32::com::Guid guid;

        /* data. */
    private:
        w32::gdi::Image myBitmap;

        /* construction. */
    public:
        Extension ()
            : myBitmap(w32::gdi::Image::proxy(0))
        {
        }

        /* overrides. */
    public:
        virtual void compute (
            const w32::gdi::Size& requestedsize, ::DWORD depth
            )
        {
                // Read the image header.
            pnm::Header header;
#if 0 // XP doesn't use initialize with stream...
            std::ifstream input(path().data(),std::ios::binary);
            if ( !input.is_open() || !(input >> header) ) {
                throw (InvalidPnmFile());
            }
#endif
            
                // Create a convenient wrapper for the stream.
            w32::shl::Stream stream(this->stream());
            w32::shl::streambuf streambuf(stream);
            
                // Read the file's header.
            std::istream input(&streambuf);
            if ( !(input >> header) ) {
                throw (InvalidPnmFile());
            }
            
                // Compute the final thumbnail size.
            const w32::gdi::Size actualsize(header.width,header.height);
            const w32::gdi::Size finalsize =
                adjust(actualsize,requestedsize);
            
                // Load the source image from the file, into the bitmap.
            w32::gdi::Image source = pnm::convert(header,input);
            
                // Store a scaled version to fit the thumbnail.
            myBitmap = w32::gdi::Image(source, finalsize);
        }

        virtual const w32::gdi::Bitmap& fetch () const {
            return (myBitmap);
        }
    };

        // This is the unique identifier used to create objects of our class.
    const w32::com::Guid Extension::guid(
        0x7b280b72,0xb570,0x41ac,0x8a,0x6e,0xee,0xbc,0x97,0xdc,0xe3,0x7b
        ); // {7B280B72-B570-41AC-8A6E-EEBC97DCE37B}

        // This is the real type of object exposed by the our dynamic library.
    typedef w32::shl::ext::BasicExtension<Extension> ExportedClass;

}

    // Compile this as a COM in-process server.
#include <w32/app/in-process-server.cpp>
