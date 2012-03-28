#ifndef _w32_net_StreamSocket_hpp__
#define _w32_net_StreamSocket_hpp__

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
#include <w32.net/Buffer.hpp>
#include <w32.net/Socket.hpp>

namespace w32 { namespace io {

    class Channel;
    class InputStream;
    class OutputStream;
    class Stream;
    class Transfer;

} }

namespace w32 { namespace net {

    class StreamSocket :
        public Socket
    {
        /* construction. */
    public:
        StreamSocket ( const Handle& handle );
        ~StreamSocket ();

        /* methods. */
    public:
        int put ( const void * buffer, int length );
        int get ( void * buffer, int length );
        bool put ( const void * data, dword size, io::Transfer& transfer );
        bool get ( void * data, dword size, io::Transfer& transfer );
        int put ( Buffer& buffer );
        int get ( Buffer& buffer );
        void put ( Buffer& buffer, io::Transfer& transfer );
        void get ( Buffer& buffer, io::Transfer& transfer );

        /*!
         * @brief Cancel all pending I/O operations for the stream.
         *
         * @note Prior to Windows Vista, this only cancels pending I/O
         *  operations issued by the calling thread.
         */
        void cancel ();

        /*!
         * @brief Cancel a specific pending I/O request.
         */
        bool cancel ( io::Transfer& transfer );

        /*!
         * @brief Block until the transfer finishes.
         */
        dword finish ( io::Transfer& transfer );

        /* operators. */
    public:
        // This kind of sucks.
        operator io::Channel () const;
        operator io::InputStream () const;
        operator io::OutputStream () const;
        operator io::Stream () const;
    };

} }

#endif /* _w32_net_StreamSocket_hpp__ */
