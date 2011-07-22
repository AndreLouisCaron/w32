#ifndef _png_hpp__
#define _png_hpp__

// (( Andre Louis Caron <andre.louis.caron@usherbrooke.ca> ))

#include <cstdio>
#include <exception>
#include <memory>
#include <string>

#include <png.h>

#define PNG_ERROR(function) \
    throw (std::exception(#function));

namespace png {

    typedef ::png_byte byte;
    typedef ::png_uint_32 uint32;
    typedef ::png_size_t size_t;

    template<class Implementation>
    class Source
    {
        /* construction. */
    protected:
        Source () {}

        /* methods. */
    public:
        void of ( ::png_struct& decoder )
        {
            ::png_set_read_fn(&decoder,
                static_cast<Implementation*>(this),
                &Source<Implementation>::read);
        }

    private:
            // Function to implement in child classes.
        size_t get ( byte * data, size_t size );

        /* class methods. */
    private:
        static void read
            ( ::png_struct * decoder, ::png_byte * data, ::png_size_t size )
        {
                // Delegate to instance method.
            reinterpret_cast< Implementation* >
                (::png_get_io_ptr(decoder))->get(data, size);
        }
    };

    template<class Implementation>
    class Sink
    {
        /* construction. */
    protected:
        Sink () {}

        /* methods. */
    public:
        void to ( ::png_struct& encoder )
        {
            ::png_set_write_fn(&encoder,
                static_cast<Implementation*>(this),
                &Sink<Implementation>::write,
                &Sink<Implementation>::flush
                );
        }

    private:
            // Functions to implement in child classes.
        size_t put ( const byte * data, size_t size );
        void flush ();

        /* class methods. */
    private:
        static void write ( ::png_struct * decoder, byte * data, size_t size )
        {
                // Delegate to instance method.
            reinterpret_cast< Implementation* >
                (::png_get_io_ptr(decoder))->put(data, size);
        }

        static void flush ( ::png_struct * decoder )
        {
                // Delegate to instance method.
            reinterpret_cast< Implementation* >
                (::png_get_io_ptr(decoder))->flush();
        }
    };

    template<class Image, class Source, class Factory>
    Image decode ( Source& source, Factory factory )
    {
            // Validate file signature.
        byte signature[8];
        source.get(signature, 8);
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
        source.of(*decoder);
        
            // Read format signature & image information.
        ::png_set_sig_bytes(decoder, 8);
        ::png_read_info(decoder, header);
        
            // Handle interlaced format.
        ::png_set_interlace_handling(decoder);
        ::png_read_update_info(decoder, header);
        
            // Windows bitmaps are stored as BGR.
        ::png_set_bgr(decoder);
        
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
            ::png_set_gray_1_2_4_to_8(decoder);
        }
        if ( decoder->bit_depth == 16 ) {
            ::png_set_strip_16(decoder);
        }
        if ( (decoder->color_type & PNG_COLOR_MASK_ALPHA) != 0 ) {
            ::png_set_strip_alpha(decoder);
        }
        
            // Allocate memory.
        Image image = factory(width, height);
        
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
        
            // Done!
        return (image);
    }

        // For use with pre-allocated image buffer.
    template<class Image, class Source>
    void decode ( const Image& image, Source& source )
    {
            // Validate file signature.
        byte signature[8];
        source.get(signature, 8);
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
        source.of(*decoder);
        
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
            ::png_set_gray_1_2_4_to_8(decoder);
        }
        if ( decoder->bit_depth == 16 ) {
            ::png_set_strip_16(decoder);
        }
        if ( (decoder->color_type & PNG_COLOR_MASK_ALPHA) != 0 ) {
            ::png_set_strip_alpha(decoder);
        }
        
            // Read using vector of pointers to pixel rows.
        byte **const rows = new byte*[height];
        byte * row = image.buffer();
        for ( uint32 y = 0; (y < height); ++y ) {
            rows[y] = row, row += image.stride();
        }
        ::png_read_image(decoder, rows);
        delete [] rows;
        
            // Cleanup.
        ::png_destroy_read_struct(&decoder, &header, 0);
    }

    template<class Image, class Sink>
    void encode ( const Image& image, Sink& sink )
    {
            // Allocate memory for encoder.
        ::png_structp encoder = ::png_create_write_struct(
            PNG_LIBPNG_VER_STRING, 0, 0, 0
            );
        if ( encoder == 0 ) {
            PNG_ERROR(png_create_write_struct);
        }
        
            // Allocate memory for image information.
        ::png_infop header = ::png_create_info_struct(encoder);
        if ( header == 0 )
        {
            ::png_destroy_read_struct(&encoder, 0, 0);
            PNG_ERROR(png_create_info_struct);
        }
        
            // Set error handler.
        if (::setjmp(png_jmpbuf(encoder)))
        {
            ::png_destroy_read_struct(&encoder, &header, 0);
            PNG_ERROR(png_something);
        }
        
            // Indicate where to write to.
        sink.to(*encoder);
        
            // Write file header.
        ::png_set_IHDR(
            encoder, header, image.width(), image.height(),
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
        ::png_write_info(encoder, header);
        
            // Read using vector of pointers to pixel rows.
        byte **const rows = new byte*[image.height()];
        byte * row = const_cast< byte* >(image.buffer());
        for ( uint32 y = 0; (y < image.height()); ++y ) {
            rows[y] = row, row += image.stride();
        }
        ::png_write_image(encoder, rows);
        delete [] rows;
        
            // Cleanup.
        ::png_destroy_write_struct(&encoder, &header);
    }


        // PNG data source for use with C-style file I/O.
    class StdcFileSource :
        public Source< StdcFileSource >
    {
        /* data. */
    private:
        std::FILE * myBackend;

        /* construction. */
    public:
        explicit StdcFileSource ( std::FILE * backend )
            : Source(), myBackend(backend)
        {
        }

        explicit StdcFileSource ( const char * path )
            : Source(), myBackend(std::fopen(path, "rb"))
        {
            if ( myBackend == 0 ) {
                throw (std::exception("File not found."));
            }
        }

        explicit StdcFileSource ( const wchar_t * path )
            : Source(), myBackend(::_wfopen(path, L"rb"))
        {
            if ( myBackend == 0 ) {
                throw (std::exception("File not found."));
            }
        }

        /* methods. */
    public:
        size_t get ( byte * data, size_t size )
        {
            const std::size_t result =
                std::fread(data, sizeof(byte), size, myBackend);
            if ( result != size )
            {
                    // Error handling!
                if ( std::feof(myBackend) ) {}
                if ( std::ferror(myBackend) ) {}
            }
            return (result);
        }
    };

        // PNG data sink for use with C-style file I/O.
    class StdcFileSink :
        public Sink< StdcFileSink >
    {
        /* data. */
    private:
        std::FILE * myBackend;

        /* construction. */
    public:
        explicit StdcFileSink ( std::FILE * backend )
            : Sink(), myBackend(backend)
        {
        }

        /* methods. */
    public:
        size_t put ( const byte * data, size_t size )
        {
            const ::size_t result =
                ::fwrite(data, sizeof(byte), size, myBackend);
            if ( result != size )
            {
                    // Error hanling!
                if ( std::feof(myBackend) ) {}
                if ( std::ferror(myBackend) ) {}
            }
            return (result);
        }

        void flush ()
        {
            if ( ::fflush(myBackend) )
            {
                    // Error hanling!
                if ( std::feof(myBackend) ) {}
                if ( std::ferror(myBackend) ) {}
            }
        }
    };

}

#endif /* _png_hpp__ */
