// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net/streambuf.hpp>

namespace w32 { namespace net {

    streambuf::streambuf ( StreamSocket& stream )
        : myStream(stream)
    {
            // Both buffers are initially empty.
        setg(myGBuf,myGBuf+GBufSize,myGBuf+GBufSize);
        setp(myPBuf,myPBuf+PBufSize);
    }

    streambuf::int_type streambuf::overflow ( int_type character )
    {
            // Try to output all characters, including the extra one.
        const std::streamsize count = myStream.put(
            pbase(),std::streamsize(pptr()-pbase())
            );
        const char_type value = traits_type::to_int_type(character);
        if ((count == 0) || (myStream.put(&value,1) == 0)) {
            return (traits_type::eof());
        }
            // Adjust output buffer.
        setp(myPBuf,myPBuf+PBufSize);
        return (traits_type::not_eof(character));
    }

    streambuf::int_type streambuf::underflow ()
    {
            // Try to extract some data. If we didn't
            // read anything, return EOF.
        const std::streamsize count = myStream.get(myGBuf,GBufSize);
        if ( count == 0 ) {
            return (traits_type::eof());
        }
            // Adjust input buffer and peek at the first character.
        setg(myGBuf,myGBuf,myGBuf+count);
        return (traits_type::to_int_type(*gptr()));
    }

    int streambuf::sync ()
    {
        const std::streamsize count = myStream.put(
            pbase(), std::streamsize(pptr()-pbase())
            );
        setp(pptr(),epptr());
        return ((count == 0)? 0 : 1);
    }

} }
