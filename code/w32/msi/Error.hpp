#ifndef _w32_msi_Error_hpp__
#define _w32_msi_Error_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <cstddef>
#include <cstdio>

namespace w32 { namespace msi {

    class Error
    {
        /* class data. */
    private:
        static const std::size_t MaximumMessageLength = 512;

        /* data. */
    private:
        char myMessage[MaximumMessageLength];

        /* construction. */
    public:
        Error (
            const char * function, ::UINT error, const char * file, int line
            );

        /* methods. */
    public:
        const char * what () const;
    };

} }

#define UNCHECKED_INSTALLER_ERROR(function,error) \
    throw (w32::msi::Error( \
        #function, error, __FILE__, __LINE__ \
        ));

#endif /* _w32_msi_Error_hpp__ */
