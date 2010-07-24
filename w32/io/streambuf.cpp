// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/streambuf.hpp>

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
