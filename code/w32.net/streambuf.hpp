#ifndef _w32_net_streambuf_hpp__
#define _w32_net_streambuf_hpp__

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

#include "__configure__.hpp"
#include <w32.net/StreamSocket.hpp>
#include <streambuf>

namespace w32 { namespace net {

        /*!
         * @brief Standard I/O stream adapter for socket streams.
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
