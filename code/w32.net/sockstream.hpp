#ifndef _w32_net_sockstream_hpp__
#define _w32_net_sockstream_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.net/StreamSocket.hpp>
#include <w32.net/streambuf.hpp>
#include <iostream>

namespace w32 { namespace net {

    class sockstream :
        public std::iostream
    {
        /* data. */
    private:
        StreamSocket& myBackend;
        streambuf myBuffer;

        /* construction. */
    public:
        sockstream ( StreamSocket& backend );

        /* methods. */
    public:
        void shutdown ( std::ios::openmode mode );
    };

} }

#endif /* _w32_net_sockstream_hpp__ */
