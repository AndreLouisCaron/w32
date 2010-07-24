#ifndef _stdc_Error_hpp__
#define _stdc_Error_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <cerrno>
#include <cstdio>
#include <cstring>

namespace stdc {

        /*!
         * @brief Exception wrapper for standard error number.
         */
    class Error
    {
        /* data. */
    private:
        char myDescription[256];

        /* construction. */
    public:
        Error ( const char * function, int error )
        {
            std::sprintf(
                "Function '%s' returned error %d: '%s'.",
                function, error, std::strerror(error)
                );
        }

        Error ( const Error& rhs )
        {
            std::strcpy(myDescription, rhs.myDescription);
        }

        /* methods. */
    public:
        const char * what () const
        {
            return (myDescription);
        }

        /* operators. */
    public:
        Error& operator= ( const Error& rhs )
        {
            std::strcpy(myDescription, rhs.myDescription);
            return (*this);
        }
    };

}

#define STDC_ERROR(function) \
    throw (stdc::Error(#function, errno));

#endif /* _stdc_Error_hpp__ */
