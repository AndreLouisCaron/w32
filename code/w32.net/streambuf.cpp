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
