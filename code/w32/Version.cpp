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

#include <w32/Version.hpp>
#include <w32/Error.hpp>

namespace w32 {

    Version Version::_2000 ()
    {
        return (Version(5, 0));
    }

    Version Version::xp ()
    {
        return (Version(5, 1));
    }

    Version Version::vista ()
    {
        return (Version(6, 0));
    }

    Version::Version ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwOSVersionInfoSize = sizeof(myData);

        const ::BOOL result = ::GetVersionExW(
            reinterpret_cast< ::OSVERSIONINFOW* >(&myData)
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetVersionEx, error);
        }
    }

    Version::Version ( dword major, dword minor )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwOSVersionInfoSize = sizeof(myData);

        myData.dwMajorVersion = major;
        myData.dwMinorVersion = minor;
    }

    Version::Data& Version::data ()
    {
        return (myData);
    }

    const Version::Data& Version::data () const
    {
        return (myData);
    }

    dword Version::major () const
    {
        return (myData.dwMajorVersion);
    }

    dword Version::minor () const
    {
        return (myData.dwMinorVersion);
    }

    dword Version::build () const
    {
        return (myData.dwBuildNumber);
    }

    bool Version::operator== ( const Version& rhs ) const
    {
        return ((major() == rhs.major()) && (minor() == rhs.minor()));
    }

    bool Version::operator< ( const Version& rhs ) const
    {
        return ((major() < rhs.major()) ||
            ((major() == rhs.major()) && (minor() < rhs.minor())));
    }

}
