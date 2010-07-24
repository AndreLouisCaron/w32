// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <com/Error.hpp>
#include <cstddef>
#include <cstdio>

namespace w32 { namespace com {

    Error::Error (
        const char * type, const char * method,
        const Result& result,
        const char * file, int line
        ) throw()
        : myResult(result)
    {
        static const char format[] =
            "Unchecked error: using %s::%s at \'%s\',"
            "line %d returned error code %x.";
        static const std::size_t length = sizeof(myMessage)-1;
        
        ::_snprintf(
            myMessage, length, format, type,
            method, file, line, myResult.value()
            );
        myMessage[length] = '\0';
    }

    const char * Error::what () const throw()
    {
        return (myMessage);
    }

    Result Error::result () const throw ()
    {
        return (myResult);
    }

} }
