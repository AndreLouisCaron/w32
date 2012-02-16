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

/*!
 * @file w32.io/streambuf.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/streambuf.hpp>
#include <iostream>

namespace w32 { namespace io {

    istreambuf::istreambuf ( InputStream& stream )
        : myStream(stream)
    {
            // Set get buffer pointers (buffer is initially empty).
        setg(myGetBuffer,myGetBuffer+GetBufferSize,myGetBuffer+GetBufferSize);
    }

    istreambuf::int_type istreambuf::underflow ()
    {
            // Input bytes to fill the get buffer.
        const std::streamsize count = myStream.get(
            reinterpret_cast<uint8*>(myGetBuffer), GetBufferSize
            );
        if ( count == 0 ) {
            return (traits_type::eof());
        }
        
            // Adjust get buffer pointers.
        setg(myGetBuffer,myGetBuffer,myGetBuffer+count);
        
            // Peek at the first character
        return (traits_type::not_eof(*gptr()));
    }

    ostreambuf::ostreambuf ( OutputStream& stream )
        : myStream(stream)
    {
            // Buffer is initially empty.
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
    }

    ostreambuf::int_type ostreambuf::overflow ( int_type character )
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myStream.put(
            reinterpret_cast<const uint8*>(pbase()),
            std::streamsize(pptr()-pbase())
            );
        const char_type value = traits_type::to_int_type(character);
        if ( count == 0 ) {
            return (traits_type::eof());
        }
        
            // Output overflowing character.
        if ( myStream.put(reinterpret_cast<const uint8*>(&value),1) == 0 ) {
            return (traits_type::eof());
        }
        
            // Adjust put buffer pointers.
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
        
            // Indicate success.
        return (traits_type::not_eof(character));
    }

    int ostreambuf::sync ()
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myStream.put(
            reinterpret_cast<const uint8*>(pbase()),
            std::streamsize(pptr()-pbase())
            );
        
            // Adjust put buffer pointers.
        setp(pptr(),epptr());
        
            // Indicate status (failure/success).
        return ((count == 0)? 0 : 1);
    }

    streambuf::streambuf ( Channel& channel )
        : myChannel(channel)
    {
            // Set buffer pointers (both are initially empty).
        setg(myGetBuffer,myGetBuffer+GetBufferSize,myGetBuffer+GetBufferSize);
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
    }

    streambuf::int_type streambuf::overflow ( int_type character )
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myChannel.put(
            reinterpret_cast<const uint8*>(pbase()),
            std::streamsize(pptr()-pbase())
            );
        const char_type value = traits_type::to_int_type(character);
        if ( count == 0 ) {
            return (traits_type::eof());
        }
        
            // Output overflowing character.
        if ( myChannel.put(reinterpret_cast<const uint8*>(&value),1) == 0 ) {
            return (traits_type::eof());
        }
        
            // Adjust put buffer pointers.
        setp(myPutBuffer,myPutBuffer+PutBufferSize);
        
            // Indicate success.
        return (traits_type::not_eof(character));
    }

    streambuf::int_type streambuf::underflow ()
    {
            // Input bytes to fill the get buffer.
        const std::streamsize count = myChannel.get(
            reinterpret_cast<uint8*>(myGetBuffer), GetBufferSize
            );
        if ( count == 0 ) {
            return (traits_type::eof());
        }
        
            // Adjust get buffer pointers.
        setg(myGetBuffer,myGetBuffer,myGetBuffer+count);
        
            // Peek at the first character.
        return (*gptr());
    }

    int streambuf::sync ()
    {
            // Ouput all contents of put buffer.
        const std::streamsize count = myChannel.put(
            reinterpret_cast<const uint8*>(pbase()),
            std::streamsize(pptr()-pbase())
            );
        
            // Adjust put buffer pointers.
        setp(pptr(),epptr());
        
            // Indicate status (failure/success).
        return ((count == 0)? 0 : 1);
    }

} }
