// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/currentdirectory.hpp>
#include <w32/Error.hpp>

namespace w32 {

    string currentdirectory ()
    {
        const ::DWORD size = ::GetCurrentDirectoryW(0, 0);
        if ( size == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetCurrentDirectory, error);
        }
        string value(size);
        const ::DWORD result = ::GetCurrentDirectoryW(size, value.data());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetCurrentDirectory, error);
        }
        return (value);
    }

}
