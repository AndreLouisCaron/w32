#ifndef _jpeg_hpp__
#define _jpeg_hpp__

// (( Andre Louis Caron <andre.louis.caron@usherbrooke.ca> ))

#include <memory>
#include <string>

    // INT32 conflicts in <jpeglib.h> and Microsoft's <basetsd.h>,
    // but <jpeglib.h> knows it. Make sure <basetsd.h> is included
    // before so that all this compiles safely.
#ifdef _WIN32
#   include <basetsd.h>
#endif
#include <setjmp.h>
#include <jpeglib.h>
#include <jerror.h>

#define JPEG_ERROR(function) \
    throw (std::exception(#function));

namespace jpeg {

    typedef ::JOCTET octet;
    typedef octet byte;
    typedef ::JDIMENSION dimension;
    typedef dimension size_t;
    typedef ::JSAMPLE sample;

    template<class Implementation, size_t BufferSize=1024>
    class Source :
        public ::jpeg_source_mgr
    {
        /* data. */
    private:
        byte myBuffer[BufferSize];

        /* construction. */
    public:
        Source ()
        {
            this->bytes_in_buffer = 0;
            this->next_input_byte = myBuffer;
        }

        /* methods. */
    public:
        void of ( ::jpeg_decompress_struct& decoder )
        {
                // Attach methods to the source manager.
            this->init_source = &Source<Implementation>::initialize;
            this->term_source = &Source<Implementation>::terminate;
            this->fill_input_buffer = &Source<Implementation>::fill;
            this->skip_input_data = &Source<Implementation>::skip;
            this->resync_to_restart = &Source<Implementation>::rewind;
            
                // Register the source manager in the JPEG decompressor.
            decoder.src = static_cast<Implementation*>(this);
        }

    protected:
        byte * buffer () { return (myBuffer); }
        dimension size () const { return (BufferSize); }

    public:
        void fill ()
        {
                // Adjust buffer pointers.
            this->bytes_in_buffer =
                static_cast< Implementation* >(this)->get(buffer(), size());
            this->next_input_byte = buffer();
        }

        void skip ( long bytes )
        {
            while ( bytes > 0 )
            {
                    // Determine maximum number of bytes we can skip at once.
                const long count =
                    std::min<long>(this->bytes_in_buffer, bytes);
                
                    // Adjust pointers.
                this->bytes_in_buffer -= count;
                this->next_input_byte += count;
                
                    // Update number of bytes to skip.
                bytes -= count;
                
                    // Read additional data if necessary.
                if ( bytes > 0 ) { fill(); }
            }
        }

        /* class methods. */
    private:
        static void initialize ( ::j_decompress_ptr )
        {
            // No-op: constructor does setup.
        }

        static void terminate ( ::j_decompress_ptr )
        {
            // No-op: destructor does cleanup.
        }

        static ::boolean fill ( ::j_decompress_ptr decoder )
        {
                // Deleagate to clean implementation.
            reinterpret_cast< Implementation* >
                (decoder->src)->fill();
            
                // Never return 0 unless using I/O suspension.
            return (1);
        }

        static void skip ( ::j_decompress_ptr decoder, long bytes )
        {
                // Deleagate to clean implementation.
            reinterpret_cast< Implementation* >
                (decoder->src)->skip(bytes);
        }

        static unsigned char rewind ( ::j_decompress_ptr decoder, int desired )
        {
                // It's recommended to use the builtin method unless we
                // have additionnal capabalities, such as seeking backward.
            return (::jpeg_resync_to_restart(decoder, desired));
        }
    };

    template<class Implementation, size_t BufferSize=1024>
    class Sink :
        public ::jpeg_destination_mgr
    {
        /* nested types. */
    private:
        typedef Sink<Implementation, BufferSize> Self;

        /* data. */
    private:
        byte myBuffer[BufferSize];

        /* construction. */
    public:
        Sink ()
        {
            this->free_in_buffer = size();
            this->next_output_byte = buffer();
        }

        /* methods. */
    public:
        void to ( ::jpeg_compress_struct& encoder )
        {
                // Attach methods to the destination manager.
            this->init_destination = &Self::initialize;
            this->term_destination = &Self::terminate;
            this->empty_output_buffer = &Self::empty;
         
                // Register the source manager in the JPEG decompressor.
            encoder.dest = static_cast<Implementation*>(this);
        }

    protected:
        byte * buffer () { return (myBuffer); }
        size_t size () const { return (BufferSize); }

    private:
        size_t put ( const byte * data, size_t size );

        void empty ()
        {
                // Assume the buffer is completely full.
            static_cast< Implementation* >(this)->put
                (buffer(), size());
            
                // Reset buffer pointers.
            this->free_in_buffer = size();
            this->next_output_byte = buffer();
        }

        void atend ()
        {
                // The buffer might not be completely full.
            static_cast< Implementation* >(this)->put
                (buffer(), size()-(this->free_in_buffer));
            
                // Reset buffer pointers.
            this->free_in_buffer = size();
            this->next_output_byte = buffer();
        }

        /* class methods. */
    private:
        static void initialize ( ::j_compress_ptr )
        {
            // No-op: constructor does setup.
        }

        static void terminate ( ::j_compress_ptr encoder )
        {
                // Deleagate to instance method.
            reinterpret_cast< Implementation* >
                (encoder->dest)->atend();
        }

        static byte empty ( ::j_compress_ptr encoder )
        {
                // Deleagate to instance method.
            reinterpret_cast< Implementation* >
                (encoder->dest)->empty();
            
                // Never return 0 unless using I/O suspension.
            return (1);
        }
    };

    class Handler :
        public ::jpeg_error_mgr
    {
        /* data. */
    public:
            // Note: can't wrap the call to setjmp() in a function call because
            // the stack has to be accessible from where the setjmp() is marked.
        ::jmp_buf state;

        /* construction. */
    public:
        Handler ()
        {
            std::memset(this, 0, sizeof(*this));
            ::jpeg_error_mgr::error_exit = &Handler::error_exit;
            ::jpeg_error_mgr::emit_message = &Handler::emit_message;
            ::jpeg_error_mgr::output_message = &Handler::output_message;
            ::jpeg_error_mgr::format_message = &Handler::format_message;
            ::jpeg_error_mgr::reset_error_mgr = &Handler::reset_error_mgr;
        }

        /* class methods. */
    private:
        static void error_exit ( ::j_common_ptr codec )
        {
            Handler *const handler =
                (Handler*)codec->err;
            ::longjmp(handler->state, 0);
        }

        static void emit_message ( ::j_common_ptr, int )
        {
        }

        static void output_message ( ::j_common_ptr )
        {
        }

        static void format_message ( ::j_common_ptr, char * buffer )
        {
        }

        static void reset_error_mgr ( ::j_common_ptr )
        {
        }
    };

    template<class Image, class Source, class Factory>
    Image decode ( Source& source, Factory factory )
    {
            // 1. Set-up error handling.
        Handler handler;
        
            // 2. Initialize a JPEG decompression object.
        ::jpeg_decompress_struct decompressor;
        std::memset(&decompressor, 0, sizeof(decompressor));
        decompressor.err = &handler;
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_create_decompress);
        }
        ::jpeg_create_decompress(&decompressor);
        
            // 3. Specify source of compressed data.
        source.of(decompressor);
        source.fill();
        
            // 4. Read stream header.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_read_header);
        }
        ::jpeg_read_header(&decompressor, TRUE);
        
            // 5. Set parameters for decompression.
        // ...
        
            // 6. Start decompression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_start_decompress);
        }
        ::jpeg_start_decompress(&decompressor);
        
            // 7. Obtain image information.
        const dimension width = decompressor.output_width;
        const dimension height = decompressor.output_height;
        const dimension components = decompressor.output_components;
        const dimension stride = width * components;
        
            // 8. Allocate image buffer.
        Image image = factory(width, height);
        
            // 9. Read data.
        sample * scanline = static_cast<sample*>(image.buffer());
        while ( decompressor.output_scanline < height )
        {
                // Read the contents of the scanline.
            if ( ::setjmp(handler.state) != 0 ) {
                JPEG_ERROR(jpeg_read_scanlines);
            }
            ::jpeg_read_scanlines(&decompressor, &scanline, 1);
            
                // Adavance to the next row.
            scanline += stride;
        }
        
            // 10. End decompression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_finish_decompress);
        }
        ::jpeg_finish_decompress(&decompressor);
        
            // 11. Release decompression object.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_destroy_decompress);
        }
        ::jpeg_destroy_decompress(&decompressor);
        
        return (image);
    }

    template<class Image, class Source>
    void decode ( Image& image, Source& source )
    {
            // 1. Set-up error handling.
        error_handler handler;
        std::memset(&handler, 0, sizeof(handler));
        handler.error_exit = &error_callback;
        
            // 2. Initialize a JPEG decompression object.
        ::jpeg_decompress_struct decompressor;
        std::memset(&decompressor, 0, sizeof(decompressor));
        decompressor.err = ::jpeg_std_error(&handler);
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_create_decompress);
        }
        ::jpeg_create_decompress(&decompressor);
        
            // 3. Specify source of compressed data.
        source.of(decompressor);
        
            // 4. Read stream header.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_read_header);
        }
        ::jpeg_read_header(&decompressor, TRUE);
        
            // 5. Set parameters for decompression.
        // ...
        
            // 6. Start decompression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_start_decompress);
        }
        ::jpeg_start_decompress(&decompressor);
        
            // 7. Obtain image information.
        const dimension width = decompressor.output_width;
        const dimension height = decompressor.output_height;
        const dimension components = decompressor.output_components;
        
            // 9. Read data.
        sample * scanline = image.buffer();
        while ( decompressor.output_scanline < height )
        {
                // Read the contents of the scanline.
            if ( ::setjmp(handler.state) != 0 ) {
                JPEG_ERROR(jpeg_read_scanlines);
            }
            ::jpeg_read_scanlines(&decompressor, &scanline, 1);
            
                // Adavance to the next row.
            scanline += image.stride();
        }
        
            // 10. End decompression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_finish_decompress);
        }
        ::jpeg_finish_decompress(&decompressor);
        
            // 11. Release decompression object.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_destroy_decompress);
        }
        ::jpeg_destroy_decompress(&decompressor);
    }

    template<class Image, class Sink>
    void encode ( const Image& image, Sink& sink )
    {
            // 1. Set-up error handling.
        error_handler handler;
        std::memset(&handler, 0, sizeof(handler));
        handler.error_exit = &error_callback;
        
            // 2. Initialize a JPEG compression object.
        ::jpeg_compress_struct compressor;
        std::memset(&compressor, 0, sizeof(compressor));
        compressor.err = ::jpeg_std_error(&handler);
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_create_compress);
        }
        ::jpeg_create_compress(&compressor);
        
            // 3. Specify destination of compressed data.
        sink.to(compressor);
        
            // 4. Set image information.
        compressor.image_width = image.width();
        compressor.image_height = image.height();
        compressor.input_components = 3;
        compressor.in_color_space = JCS_RGB;
        
            // 5. Set parameters for compression.
        ::jpeg_set_defaults(&compressor);
        
            // 6. Start compression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_start_compress);
        }
        ::jpeg_start_compress(&compressor, TRUE);
        
            // 7. Write data.
        const sample * scanline = static_cast<const sample*>(image.buffer());
        while ( compressor.next_scanline < compressor.image_height )
        {
                // Write the contents of the scanline.
            if ( ::setjmp(handler.state) != 0 ) {
                JPEG_ERROR(jpeg_write_scanlines);
            }
            ::jpeg_write_scanlines(
                &compressor, const_cast<sample**>(&scanline), 1
                );
            
                // Adavance to the next row.
            scanline += image.stride();
        }
        
            // 8. End compression.
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_finish_compress);
        }
        ::jpeg_finish_compress(&compressor);
        
            // 9. Release compression object.
        ::jpeg_destroy_compress(&compressor);
        if ( ::setjmp(handler.state) != 0 ) {
            JPEG_ERROR(jpeg_destroy_compress);
        }
    }

    class StdcFileSource :
        public Source< StdcFileSource >
    {
        /* data. */
    private:
        std::FILE * myBackend;

        /* construction. */
    public:
        explicit StdcFileSource ( std::FILE * backend )
            : myBackend(backend)
        {
        }

        /* methods. */
    public:
        size_t get ( byte * data, size_t size )
        {
            return (::fread(data, sizeof(byte), size, myBackend));
        }
    };

    class StdcFileSink :
        public Sink< StdcFileSink, 4096 >
    {
        /* data. */
    private:
        std::FILE * myBackend;

        /* construction. */
    public:
        explicit StdcFileSink ( std::FILE * backend )
            : myBackend(backend)
        {
        }

        /* methods. */
    public:
        size_t put ( const byte * data, size_t size )
        {
            return (::fwrite(data, sizeof(byte), size, myBackend));
        }
    };

}

#endif /* _jpeg_hpp__ */
