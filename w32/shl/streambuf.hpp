#ifndef _win_shl_streambuf_hpp__
#define _win_shl_streambuf_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl/Stream.hpp>
#include <streambuf>

namespace w32 { namespace shl {

        /*!
         * @brief Standard I/O stream adapter for i/o streams.
         */
    class W32_SHL_EXPORT streambuf :
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
        Stream &myStream;
        char_type myGetBuffer[GetBufferSize];
        char_type myPutBuffer[PutBufferSize];

        /* construction. */
    public:
            /*!
             * @brief Build a stream buffer that uses a Tcp/Ip stream.
             * @param stream The i/o stream to use.
             */
        streambuf ( Stream& stream );

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

#endif /* _win_shl_streambuf_hpp__ */
