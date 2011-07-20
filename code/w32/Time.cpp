// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Time.hpp>
#include <w32/Error.hpp>

namespace w32 {

    Time Time::now ()
    {
        ::SYSTEMTIME time;
        ::GetSystemTime(&time);
        return (Time(time));
    }

    Time::Time ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    Time::Time ( const Data& value )
        : myData(value)
    {
    }

    Time::Time ( const ::FILETIME& value )
    {
        const ::BOOL result = ::FileTimeToSystemTime(&value,&myData);
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(FileTimeToSystemTime,::GetLastError());
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

    word Time::year () const
    {
        return (myData.wYear);
    }

    word Time::month () const
    {
        return (myData.wMonth);
    }

    word Time::day () const
    {
        return (myData.wDay);
    }

    word Time::hour () const
    {
        return (myData.wHour);
    }

    word Time::minute () const
    {
        return (myData.wMinute);
    }

    word Time::second () const
    {
        return (myData.wSecond);
    }

    word Time::millisecond () const
    {
        return (myData.wMilliseconds);
    }

}
