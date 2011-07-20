// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/image.hpp>
#include <w32/gdi/DeviceContext.hpp>
#include <algorithm>

    // Codecs are implemented in C and require C file input/output.
#include "stdc/InputFile.hpp"
#include "stdc/OutputFile.hpp"

    // Accept Portable Network Graphics image files.
#include <png.h>

    // Accept Joint Photographic Exports Group image files.
#include <jpeglib.h>
#include <jerror.h>

    // Try to link automagically.
#ifdef _MSC_VER
#   pragma comment ( lib, "jpeg.lib" )
#   pragma comment ( lib, "libpng.lib" )
#   pragma comment ( lib, "zlib.lib" )
#endif

#define PNG_ERROR(function) \
    throw (std::exception(#function));

namespace png {

    typedef png_uint_32 uint32;
    typedef png_byte byte;

    w32::gdi::Image decode ( const wchar_t * path )
    {
            // Open input file.
        stdc::InputFile input(path);
        
            // Validate file signature.
        byte signature[8];
        ::fread(signature, 1, 8, input.handle());
        if (::png_sig_cmp(signature, 0, 8)) {
            PNG_ERROR(png_sig_cmp);
        }
        
            // Allocate memory for decoder.
        ::png_structp decoder = ::png_create_read_struct(
                                    PNG_LIBPNG_VER_STRING, 0, 0, 0
                                );
        if ( decoder == 0 ) {
            PNG_ERROR(png_create_read_struct);
        }
        
            // Allocate memory for image information.
        ::png_infop header = ::png_create_info_struct(decoder);
        if ( header == 0 )
        {
            ::png_destroy_read_struct(&decoder, 0, 0);
            PNG_ERROR(png_create_info_struct);
        }
        
            // Set error handler.
        if (::setjmp(png_jmpbuf(decoder)))
        {
            ::png_destroy_read_struct(&decoder, &header, 0);
            PNG_ERROR(png_something);
        }
        
            // Indicate where to read from.
        ::png_init_io(decoder, input.handle());
        
            // Read format signature & image information.
        ::png_set_sig_bytes(decoder, 8);
        ::png_read_info(decoder, header);
        
            // Handle interlaced format.
        ::png_set_interlace_handling(decoder);
        ::png_read_update_info(decoder, header);
        
        const uint32 width = decoder->width;
        const uint32 height = decoder->height;
        const uint32 stride = width * 3;
        
            // Always resquest RGB24 images.
        if ( decoder->color_type == PNG_COLOR_TYPE_PALETTE ) {
            ::png_set_palette_to_rgb(decoder);
        }
        if ((decoder->color_type == PNG_COLOR_TYPE_GRAY)
                && (decoder->bit_depth < 8))
        {
            ::png_set_expand_gray_1_2_4_to_8(decoder);
        }
        if ( decoder->bit_depth == 16 ) {
            ::png_set_strip_16(decoder);
        }
        if ( (decoder->color_type & PNG_COLOR_MASK_ALPHA) != 0 ) {
            ::png_set_strip_alpha(decoder);
        }
        
            // Allocate memory.
        w32::gdi::Image image(
            w32::gdi::Size(long(width), -long(height)), 24
            );
        
            // Read using vector of pointers to pixel rows.
        byte **const rows = new byte*[height];
        byte * row = static_cast<byte*>(image.buffer());
        for ( uint32 y = 0; (y < height); ++y ) {
            rows[y] = row, row += stride;
        }
        ::png_read_image(decoder, rows);
        delete [] rows;
        
            // Cleanup.
        ::png_destroy_read_struct(&decoder, &header, 0);
        
            // Return the *painfully* acquired image.
        return (image);
    }

}

#define JPEG_ERROR(function) \
    throw (std::exception(#function));

namespace jpeg {

    typedef ::JDIMENSION dimension;
    typedef ::JSAMPLE sample;

    struct error_handler :
            ::jpeg_error_mgr
    {
        ::jmp_buf state;
    };

    void error_callback ( ::j_common_ptr codec )
    {
        error_handler *const handler =
            (error_handler*)codec->err;
        
        ::longjmp(handler->state, 0);
    }

    w32::gdi::Image decode ( const wchar_t * path )
    {
            // 0. Open the input file.
        stdc::InputFile myFile(path);
        
            // 1. Set-up error handling.
        error_handler myHandler;
        std::memset(&myHandler, 0, sizeof(myHandler));
        myHandler.error_exit = &error_callback;
        
            // 2. Initialize a JPEG decompression object.
        ::jpeg_decompress_struct myData;
        std::memset(&myData, 0, sizeof(myData));
        myData.err = ::jpeg_std_error(&myHandler);
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_create_decompress);
        }
        ::jpeg_create_decompress(&myData);
        
            // 3. Specify source of compressed data.
        ::jpeg_stdio_src(&myData, myFile.handle());
        
            // 4. Read stream header.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_read_header);
        }
        ::jpeg_read_header(&myData, TRUE);
        
        // 5. Set parameters for decompression.
        // ...
        
            // 6. Start decompression.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_start_decompress);
        }
        ::jpeg_start_decompress(&myData);
        
            // 7. Obtain image information.
        const dimension width = myData.output_width;
        const dimension height = myData.output_height;
        const dimension components = myData.output_components;
        const dimension stride = width * components;
        
            // 8. Allocate image buffer.
        w32::gdi::Image image(
            w32::gdi::Size(long(width), -long(height)), 8*components
        );
        sample * samples = static_cast<sample*>(image.buffer());
        
            // 9. Read data.
        sample * scanline = samples;
        while ( myData.output_scanline < height )
        {
                // Read the contents of the scanline.
            if ( ::setjmp(myHandler.state) != 0 ) {
                JPEG_ERROR(jpeg_read_scanlines);
            }
            ::jpeg_read_scanlines(&myData, &scanline, 1);
            
                // Adavance to the next row.
            scanline += stride;
        }
        
            // 10. End decompression.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_finish_decompress);
        }
        ::jpeg_finish_decompress(&myData);
        
            // 11. Release decompression object.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_destroy_decompress);
        }
        ::jpeg_destroy_decompress(&myData);
        
        return (image);
    }

    void encode ( const w32::gdi::Image& image, const wchar_t * path )
    {
            // 0. Create output file.
        stdc::OutputFile myFile(path);
        
            // 1. Set-up error handling.
        error_handler myHandler;
        std::memset(&myHandler, 0, sizeof(myHandler));
        myHandler.error_exit = &error_callback;
        
            // 2. Initialize a JPEG compression object.
        ::jpeg_compress_struct myData;
        std::memset(&myData, 0, sizeof(myData));
        myData.err = ::jpeg_std_error(&myHandler);
        myData.err = ::jpeg_std_error(&myHandler);
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_create_compress);
        }
        ::jpeg_create_compress(&myData);
        
            // 3. Specify destination of compressed data.
        ::jpeg_stdio_dest(&myData, myFile.handle());
        
            // 4. Set image information.
        w32::gdi::Image::Info info(image);
        myData.image_width = info.width();
        myData.image_height = -info.height();
        myData.input_components = 3;
        myData.in_color_space = JCS_RGB;
        const dimension stride = myData.image_width * myData.input_components;
        
            // 5. Set parameters for compression.
        ::jpeg_set_defaults(&myData);
        
            // 6. Start compression.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_start_compress);
        }
        ::jpeg_start_compress(&myData, TRUE);
        
            // 7. Read data.
        const sample * scanline = static_cast<const sample*>(image.buffer());
        while ( myData.next_scanline < myData.image_height )
        {
                // Write the contents of the scanline.
            if ( ::setjmp(myHandler.state) != 0 ) {
                JPEG_ERROR(jpeg_write_scanlines);
            }
            ::jpeg_write_scanlines(
                &myData, const_cast<sample**>(&scanline), 1
                );
            
                // Adavance to the next row.
            scanline += stride;
        }
        
            // 8. End compression.
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_finish_compress);
        }
        ::jpeg_finish_compress(&myData);
        
            // 9. Release compression object.
        ::jpeg_destroy_compress(&myData);
        if ( ::setjmp(myHandler.state) != 0 ) {
            JPEG_ERROR(jpeg_destroy_compress);
        }
    }

}

namespace {

    bool matches ( const w32::string& path, const w32::string& extension )
    {
        w32::string::const_iterator match = std::search(
                                                path.begin(), path.end(), extension.begin(), extension.end()
                                            );
        return (std::distance(match, path.end()) == extension.length()+1);
    }

}

namespace w32 { namespace gdi {

    Image image ( const string& path )
    {
        if ( matches(path, L".bmp") )
        {
                // Use standard windows bitmap loader.
            return (FileBitmap(path));
        }
        
        if ( matches(path, L".jpg") || matches(path, L".jpeg") ) {
            return (jpeg::decode(path.c_str()));
        }
        
        if ( matches(path, L".png") ) {
            return (png::decode(path.c_str()));
        }
        
        return (Image(Image::proxy(0)));
    }

    void image ( const Image& image, const string& path )
    {
        if ( image.handle() == 0 ) {
            return;
        }
        
        if ( matches(path, L".bmp") ) {
            image.save(path);
        }
        
        if ( matches(path, L".jpg") || matches(path, L".jpeg") ) {
            jpeg::encode(image, path.c_str());
        }
    }

} }
