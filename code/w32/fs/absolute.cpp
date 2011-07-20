// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/absolute.hpp>
#include <w32/Error.hpp>
#include <algorithm>
#include <iterator>

namespace {

    typedef std::reverse_iterator< w32::string::iterator > reverse;

}

namespace w32 { namespace fs {

    string absolute ( const string& directory )
    {
            // Query the length of the path.
        static wchar_t dummy[] = { L'\0' };
        ::DWORD result = ::GetFullPathNameW(directory.c_str(),0,dummy,0);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetFullPathName,::GetLastError());
        }
        
            // Get the actual value.
        string path(result+1, '\0');
        result = ::GetFullPathNameW(
            directory.c_str(), path.size(), &*path.begin(),0
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetFullPathName,::GetLastError());
        }
        path[result] = '\\';
        
                // Trim exceeding characters, if any.
        string::iterator end = std::find(
            ::reverse(path.end()), ::reverse(path.begin()), L'\\').base();
        end = std::copy(path.begin(), end, path.begin());
        path.erase(end, path.end());
        
        return (L"\\??\\" + path);
    }

} }
