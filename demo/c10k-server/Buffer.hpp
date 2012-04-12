#ifndef _server_Buffer_hpp__
#define _server_Buffer_hpp__

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

#include <w32.net.hpp>
#include <w32.io.hpp>
#include "ring.hpp"

namespace server {

    class Buffer :
        private w32::NotCopyable
    {
        /* nested types. */
    public:
        typedef ring::byte byte;

        /* data. */
    private:
        byte *const myData;
        ring myRing;

        /* construction. */
    public:
        Buffer ( std::size_t size );
        ~Buffer ();

        /* methods. */
    public:
        std::size_t size () const;
        std::size_t free () const;
        std::size_t put ( const byte * data, std::size_t size );
        std::size_t put ( const void * data, std::size_t size );
        std::size_t get ( void * data, std::size_t size );
        std::size_t peek ( byte item ) const;
    };

    class IBuffer :
        public Buffer
    {
        /* data. */
    private:
        const std::size_t mySize;
        char *const myData;
        w32::io::Transfer myOp;
        bool myReady;
        w32::qword myCounter;

        /* construction. */
    public:
        IBuffer ( std::size_t total, std::size_t perop );

        /* methods. */
    public:
        bool owns ( const w32::io::Transfer& op ) const;
        void did ( w32::dword size );
        using Buffer::get;
        void get ( w32::net::StreamSocket& stream );
        void get ( w32::io::InputStream& stream );
    };

    class OBuffer :
        public Buffer
    {
        /* data. */
    private:
        const std::size_t mySize;
        char *const myData;
        w32::io::Transfer myOp;
        bool myReady;
        w32::qword myCounter;

        /* construction. */
    public:
        OBuffer ( std::size_t total, std::size_t perop );

        /* methods. */
    public:
        bool owns ( const w32::io::Transfer& op ) const;
        void did ( w32::dword size );
        using Buffer::put;
        void put ( w32::net::StreamSocket& stream );
        void put ( w32::io::OutputStream& stream );
    };

        // Transfer all the output buffer can hold.
    void operator<< ( OBuffer& pbuf, IBuffer& gbuf );

}

#endif /* _server_Buffer_hpp__ */
