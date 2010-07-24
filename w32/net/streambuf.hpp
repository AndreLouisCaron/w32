#ifndef _w32_net_streambuf_hpp__
#define _w32_net_streambuf_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/net/StreamSocket.hpp>
#include <streambuf>

namespace w32 { namespace net {

        /*!
         * @brief Standard I/O stream adapter for socket streams.
         */
    class W32_NET_EXPORT streambuf :
        public std::basic_streambuf< char, std::char_traits<char> >
    {
        /* nested types. */
    private:
            // Shortcut to base class name.
        typedef std::basic_streambuf< char, std::char_traits<char> > base;

        /* shared data. */
    private:
            // Get and put buffer sizes.
        static const std::size_t GBufSize = 256;
        static const std::size_t PBufSize = 256;

        /* data. */
    private:
        StreamSocket myStream;
        char_type myGBuf[GBufSize];
        char_type myPBuf[PBufSize];

        /* construction. */
    public:
            /*!
             * @brief Build a stream buffer that uses a Tcp/Ip stream.
             * @param stream The Tcp/Ip stream to use.
             */
        streambuf ( StreamSocket& stream );

        /* methods. */
    protected:
            /*!
             * @brief Flush the output buffer, plus a character.
             * @return EOF on failure, something else otherwise.
             */
        virtual int_type overflow (
            int_type character = base::traits_type::eof()
            );

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

#endif /* _w32_net_streambuf_hpp__ */
