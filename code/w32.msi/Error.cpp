// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.msi/Error.hpp>

namespace w32 { namespace msi {

    Error::Error (
        const char * function, ::UINT error, const char * file, int line
        )
    {
        static const char format[] =
            "%s() failed, returning %d (%s: line %d).";
        const int result = ::_snprintf(
            myMessage, MaximumMessageLength-1, format,
            function, error, file, line
            );
        myMessage[result] = '\0';
    }

    const char * Error::what () const
    {
        return (myMessage);
    }

} }
