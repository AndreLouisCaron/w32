// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/computername.hpp>
#include <w32/Error.hpp>

namespace w32 {

    string computername ()
    {
        ::WCHAR name[MAX_COMPUTERNAME_LENGTH+1];
        ::DWORD length = MAX_COMPUTERNAME_LENGTH;
        const ::BOOL result = ::GetComputerNameW(name, &length);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_BUFFER_OVERFLOW ) {
            }
            UNCHECKED_WIN32C_ERROR(GetComputerName, error);
        }
        return (name);
    }

}
