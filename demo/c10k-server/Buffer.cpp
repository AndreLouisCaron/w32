// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
