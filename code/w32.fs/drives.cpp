// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.fs/drives.hpp>
#include <w32/Error.hpp>

namespace {

    ::DWORD length ()
    {
        static wchar_t dummy[] = { '\0' };
        return (::GetLogicalDriveStringsW(0, dummy));
    }

}

namespace w32 { namespace fs {

    mstring drives ()
    {
        const ::DWORD size = length();
        wchar_t *const data = new wchar_t[size];
        if ( ::GetLogicalDriveStringsW(size, data) == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetLogicalDriveStrings,::GetLastError());
        }
        return (mstring(string::box(data, size)));
    }

} }
