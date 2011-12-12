// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.io/InputFile.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ( ::LPCWSTR path, ::DWORD sharing, ::DWORD mode )
    {
        const ::HANDLE handle = ::CreateFileW(
            path, GENERIC_READ, sharing, 0, mode, 0, 0
            );
        if ( handle == INVALID_HANDLE_VALUE ) {
            UNCHECKED_WIN32C_ERROR(CreateFile,::GetLastError());
        }
        return (handle);
    }

}

namespace w32 { namespace io {

    InputFile::InputFile ( const string& path )
        : InputStream(Object::claim(
              ::open(path.c_str(), FILE_SHARE_READ, OPEN_EXISTING)
              ))
    {
    }

} }
