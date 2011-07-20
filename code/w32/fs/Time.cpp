// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/Time.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace fs {

    Time::Time ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    Time::Time ( const ::FILETIME& value )
        : myData(value)
    {
    }

    Time::Time ( const ::SYSTEMTIME& value )
    {
        const ::BOOL result = ::SystemTimeToFileTime(&value,&myData);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SystemTimeToFileTime,::GetLastError());
        }
    }

    Time::Time ( const w32::Time& value )
    {
        const ::BOOL result = ::SystemTimeToFileTime(&value.data(),&myData);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(SystemTimeToFileTime,::GetLastError());
        }
    }

    Time::Data& Time::data ()
    {
        return (myData);
    }

    const Time::Data& Time::data () const
    {
        return (myData);
    }

    dword Time::low () const
    {
        return (myData.dwLowDateTime);
    }

    dword Time::high () const
    {
        return (myData.dwHighDateTime);
    }

    Time::operator w32::Time () const
    {
        w32::Time value;
        const ::BOOL result = ::FileTimeToSystemTime(&myData, &value.data());
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(FileTimeToSystemTime,::GetLastError());
        }
        return (value);
    }

} }
