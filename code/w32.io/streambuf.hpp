#ifndef _w32_io_streambuf_hpp__
#define _w32_io_streambuf_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/streambuf.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32.io/Channel.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/OutputStream.hpp>
#include <streambuf>

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     * @brief Standard I/O stream adapter for input streams.
     */
    class istreambuf :
        public std::basic_streambuf< char, std::char_traits<char> >
    {
        /* nested types. */
    private:
            // Shortcut to base class name.
        typedef std::basic_streambuf< char, std::char_traits<char> > base;

        /* shared data. */
    private:
            // Get buffer size.
        static const std::size_t GetBufferSize = 256;

        /* data. */
    private:
        InputStream &myStream;
        char_type myGetBuffer[GetBufferSize];

        /* construction. */
    public:
            /*!
             * @brief Build a stream buffer that uses a Tcp/Ip stream.
             * @param stream The i/o channel to use.
             */
        istreambuf ( InputStream& stream );

        /* overrides. */
    protected:
            /*!
             * @brief Read characters into the input buffer and peek at the
             *    first value.
             * @return The value of the first character read or EOF on failure.
             */
        virtual int_type underflow ();
    };

        /*!
         * @brief Standard I/O stream adapter for output streams.
         */
    class ostreambuf :
        public std::basic_streambuf< char, std::char_traits<char> >
    {
        /* nested types. */
    private:
            // Shortcut to base class name.
        typedef std::basic_streambuf< char, std::char_traits<char> > base;

        /* shared data. */
    private:
            // Put buffer size.
        static const std::size_t PutBufferSize = 256;

        /* data. */
    private:
        OutputStream &myStream;
        char_type myPutBuffer[PutBufferSize];

        /* construction. */
    public:
            /*!
             * @brief Build a stream buffer that uses a Tcp/Ip stream.
             * @param stream The i/o stream to use.
             */
        ostreambuf ( OutputStream& stream );

        /* overrides. */
    protected:
            /*!
             * @brief Flush the output buffer, plus a character.
             * @return EOF on failure, something else otherwise.
             */
        virtual int_type overflow ( int_type character );

            /*!
             * @brief Flush the output buffer.
             * @return 1 on success, 0 on failure.
             */
        virtual int sync ();
    };

        /*!
         * @brief Standard I/O stream adapter for i/o channels.
         */
    class streambuf :
        public std::basic_streambuf< char, std::char_traits<char> >
    {
        /* nested types. */
    private:
            // Shortcut to base class name.
        typedef std::basic_streambuf< char, std::char_traits<char> > base;

        /* shared data. */
    private:
            // Get and put buffer sizes.
        static const std::size_t GetBufferSize = 256;
        static const std::size_t PutBufferSize = 256;

        /* data. */
    private:
        Channel &myChannel;
        char_type myGetBuffer[GetBufferSize];
        char_type myPutBuffer[PutBufferSize];

        /* construction. */
    public:
            /*!
             * @brief Build a stream buffer that uses a Tcp/Ip stream.
             * @param channel The i/o channel to use.
             */
        streambuf ( Channel& channel );

        /* overrides. */
    protected:
            /*!
             * @brief Flush the output buffer, plus a character.
             * @return EOF on failure, something else otherwise.
             */
        virtual int_type overflow ( int_type character );

            /*!
             * @brief Read characters into the input buffer and peek at the
             *    first value.
             * @return The value of the first character read or EOF on failure.
             */
        virtual int_type underflow ();

            /*!
             * @brief Flush the output buffer.
             * @return 1 on success, 0 on failure.
             */
        virtual int sync ();
    };

} }

#endif /* _w32_io_streambuf_hpp__ */
