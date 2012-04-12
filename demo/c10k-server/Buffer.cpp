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

#include "Buffer.hpp"
#include <w32.hpp>

namespace server {

    Buffer::Buffer ( std::size_t size )
        : myData(new ring::byte[size]),
          myRing(myData, myData+size)
    {
    }

    Buffer::~Buffer ()
    {
        delete [] myData;
    }

    std::size_t Buffer::size () const
    {
        return (myRing.size());
    }

    std::size_t Buffer::free () const
    {
        return (myRing.capacity() - myRing.size());
    }

    std::size_t Buffer::put ( const byte * data, std::size_t size )
    {
        return (std::distance(data, myRing.put(data, data+size)));
    }

    std::size_t Buffer::put ( const void * data, std::size_t size )
    {
        return (put(static_cast<const byte*>(data), size));
    }

    std::size_t Buffer::get ( void * data, std::size_t size )
    {
        return (myRing.get(data, size));
    }

    std::size_t Buffer::peek ( byte item ) const
    {
        return (myRing.peek(item));
    }

    IBuffer::IBuffer ( std::size_t total, std::size_t perop )
        : Buffer(total), mySize(perop), myData(new char[mySize]),
          myReady(true), myCounter(0)
    {
    }

    bool IBuffer::owns ( const w32::io::Transfer& op ) const
    {
        return (&op == &myOp);
    }

    void IBuffer::did ( w32::dword size )
    {
        Buffer::put(myData, size); myOp.clear();
        myCounter += size; myReady = true;
    }

    void IBuffer::get ( w32::net::StreamSocket& stream )
    try
    {
            // Sorry, can't allow simultaneous transfers.
        if ( !myReady ) { return; }
        
            // Recv whatever is available, up to transfer buffer size.
        const std::size_t size = std::min(Buffer::free(), mySize);
        if ( size > 0 ) {
            stream.get(myData, size, myOp); myReady = false;
        }
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  == getting: " << error << "." << std::endl;
    }

    void IBuffer::get ( w32::io::InputStream& stream )
    try
    {
            // Sorry, can't allow simultaneous transfers.
        if ( !myReady ) { return; }
        
            // Recv whatever is available, up to transfer buffer size.
        const std::size_t size = std::min(Buffer::free(), mySize);
        if ( size > 0 ) {
             myOp.at(myCounter); stream.get(myData, size, myOp); myReady = false;
        }
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  == getting: " << error << "." << std::endl;
    }

    OBuffer::OBuffer ( std::size_t total, std::size_t perop )
        : Buffer(total), mySize(perop), myData(new char[mySize]),
          myReady(true), myCounter(0)
    {
    }

    bool OBuffer::owns ( const w32::io::Transfer& op ) const
    {
        return (&op == &myOp);
    }

    void OBuffer::did ( w32::dword size )
    {
        myOp.clear(); myCounter += size; myReady = true;
    }

    void OBuffer::put ( w32::net::StreamSocket& stream )
    try
    {
            // Sorry, can't allow simultaneous transfers.
        if ( !myReady ) { return; }
        
            // Send whatever is available, up to transfer buffer size.
        const std::size_t size = std::min(Buffer::size(), mySize);
        if ( size > 0 ) {
            Buffer::get(myData, size);
            stream.put(myData, size, myOp); myReady = false;
        }
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  == putting: " << error << "." << std::endl;
    }

    void OBuffer::put ( w32::io::OutputStream& stream )
    try
    {
            // Sorry, can't allow simultaneous transfers.
        if ( !myReady ) { return; }
        
            // Send whatever is available, up to transfer buffer size.
        const std::size_t size = std::min(Buffer::size(), mySize);
        if ( size > 0 ) {
            Buffer::get(myData, size); myOp.at(myCounter);
            stream.put(myData, size, myOp); myReady = false;
        }
    }
    catch ( const w32::Error& error )
    {
        std::cerr << "  == putting: " << error << "." << std::endl;
    }

    void operator<< ( OBuffer& pbuf, IBuffer& gbuf )
    {
        static const std::size_t maxsize = 256;
        char buffer[maxsize];
        
            // Transfer all the output buffer can hold.
        std::size_t size = std::min(maxsize, pbuf.free());
        while ( (size=gbuf.get(buffer,size)) > 0 )
        {
            pbuf.put(buffer, size);
            size = std::min(maxsize, pbuf.free());
        }
    }

}
