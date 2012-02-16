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

#include <w32.shl/streambuf.hpp>

namespace w32 { namespace shl {

    streambuf::streambuf ( Stream& stream )
        : myStream(stream)
    {
            // Set buffer pointers (both are initially empty).
        setg(myGetBuffer,myGetBuffer+GetBufferSize,myGetBuffer+GetBufferSize);
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
    }

    streambuf::int_type streambuf::overflow ( int_type character )
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myStream.write(
            pbase(), ::ULONG(pptr()-pbase())
            );
        if ( count == 0 ) {
            return (traits_type::eof());
        }
            // Output overflowing character.
        const char_type value = traits_type::to_int_type(character);
        if ( myStream.write(&value,1) == 0 ) {
            return (traits_type::eof());
        }
            // Adjust put buffer pointers.
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
        return (traits_type::not_eof(character));
    }

    streambuf::int_type streambuf::underflow ()
    {   
            // Input bytes to fill the get buffer.
        const std::streamsize count = myStream.read(myGetBuffer,GetBufferSize);
        if ( count == 0 ) {
            return (traits_type::eof());
        }
            // Adjust get buffer pointers.
        setg(myGetBuffer,myGetBuffer,myGetBuffer+count);
            // Peek at the first character.
        return (traits_type::to_int_type(*gptr()));
    }

    int streambuf::sync ()
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myStream.write(
            pbase(), ::ULONG(pptr()-pbase())
            );
            // Adjust put buffer pointers.
        setp(pptr(),epptr());
            // Indicate status (failure/success).
        return ((count == 0)? 0 : 1);
    }

} }
