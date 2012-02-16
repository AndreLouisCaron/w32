// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.fs/absolute.hpp>
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
