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

#include <w32/Time.hpp>
#include <w32/Delta.hpp>
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

    Time& Time::operator+= ( const Delta& delta )
    {
        // Convert to file time.
        ::FILETIME time; ::SystemTimeToFileTime(&myData, &time);

        // Perform computation in number of ticks.
        ::ULARGE_INTEGER result =
            { time.dwLowDateTime, time.dwHighDateTime };
        result.QuadPart += delta.ticks();
        time.dwLowDateTime = result.LowPart;
        time.dwHighDateTime = result.HighPart;

        // Convert back to system time.
        ::FileTimeToSystemTime(&time, &myData);

        return (*this);
    }

    Time operator+ ( const Time& time, const Delta& delta )
    {
        Time result = time; result += delta; return (result);
    }

}
