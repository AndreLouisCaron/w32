#ifndef _server_Buffer_hpp__
#define _server_Buffer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
