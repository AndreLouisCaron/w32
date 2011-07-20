// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/symlink.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace fs {

    void symlink ( const string& target, const string& alias )
    {
        ::DWORD flags = 0;
        ::DWORD attributes = ::GetFileAttributesW(target.c_str());
        if ( (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ) {
            flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
        }
        const ::BOOL result = ::CreateSymbolicLinkW(
            alias.c_str(), target.c_str(), flags
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(CreateSymbolicLink,::GetLastError());
        }
    }

} }
