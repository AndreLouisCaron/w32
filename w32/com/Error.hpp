#ifndef _w32_com_Error_hpp__
#define _w32_com_Error_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Result.hpp>

namespace w32{ namespace com {

    class W32_COM_EXPORT Error
    {
        /* data. */
    private:
        Result myResult;
        char myMessage[256];

        /* construction. */
    public:
        Error (
            const char * type, const char * method,
            const Result& result,
            const char * file, int line
            ) throw();

        /* methods. */
    public:
        const char * what () const throw();
        Result result () const throw ();
    };

} }

    // Use this to throw errors using COM interfaces.
#define UNCHECKED_COM_ERROR(type,method,result) \
    throw (w32::com::Error(      \
       #type, #method, result, __FILE__, __LINE__   \
    ));

#endif /* _w32_com_Error_hpp__ */
