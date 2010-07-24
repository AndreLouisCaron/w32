// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
