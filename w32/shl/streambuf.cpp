// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/streambuf.hpp>

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
        const char_type value = traits_type::to_int_type(character);
        if ( count == 0 ) {
            return (traits_type::eof());
        }

            // Output overflowing character.
        if ( myStream.write(&value,1) == 0 ) {
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
        const std::streamsize count = myStream.read(myGetBuffer,GetBufferSize);
        if ( count == 0 ) {
            return (traits_type::eof());
        }

            // Adjust get buffer pointers.
        setg(myGetBuffer,myGetBuffer,myGetBuffer+count);

            // Peek at the first character.
        return (traits_type::not_eof(*gptr()));
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
