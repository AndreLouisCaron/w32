#ifndef _w32_net_StreamSocket_hpp__
#define _w32_net_StreamSocket_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.io/Channel.hpp>
#include <w32.io/Transfer.hpp>
#include <w32.net/Buffer.hpp>
#include <w32.net/Socket.hpp>

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
        int put ( Buffer& buffer );
        int get ( Buffer& buffer );
        void put ( Buffer& buffer, io::Transfer& transfer );
        void get ( Buffer& buffer, io::Transfer& transfer );

        /* operators. */
    public:
            // This kind of sucks.
        operator io::Channel () const;
    };

} }

#endif /* _w32_net_StreamSocket_hpp__ */
