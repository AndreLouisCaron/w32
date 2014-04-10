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

#include <w32/Waitable.hpp>
#include <w32/Error.hpp>
#include <algorithm>

namespace {

    ::DWORD wait
        ( const ::HANDLE * handles, ::DWORD count, ::BOOL all, ::DWORD timeout )
    {
        const ::DWORD result = ::WaitForMultipleObjects(
            count, handles, all, timeout
            );
        if ( result == WAIT_FAILED )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(WaitForMultipleObjects, error);
        }
        if ( result == WAIT_TIMEOUT )
        {
        }
        if ((result >= WAIT_ABANDONED_0) &&
            (result < (WAIT_ABANDONED_0+count)))
        {
        }
        return (result - WAIT_OBJECT_0);
    }

}

namespace w32 {

    dword Waitable::any ( const Set& set )
    {
        return (::wait(set.data(), set.size(), FALSE, INFINITE));
    }

    dword Waitable::any ( const Set& set, const w32::Timespan& timeout )
    {
        return (::wait(set.data(), set.size(), FALSE, timeout.ticks()));
    }

    dword Waitable::all ( const Set& set )
    {
        return (::wait(set.data(), set.size(), TRUE, INFINITE));
    }

    dword Waitable::all ( const Set& set, const w32::Timespan& timeout )
    {
        return (::wait(set.data(), set.size(), TRUE, timeout.ticks()));
    }

    Waitable::Waitable ( const Handle& handle )
        : Object(handle)
    {
    }

    void Waitable::wait () const
    {
        const ::DWORD result = ::WaitForSingleObject(handle(), INFINITE);
        if ( result == WAIT_FAILED )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(WaitForSingleObject, error);
        }
    }

    bool Waitable::wait ( const Timespan& timeout ) const
    {
        const ::DWORD result = ::WaitForSingleObject(
            handle(), timeout.ticks()
            );
        if ( result == WAIT_FAILED )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(WaitForSingleObject, error);
        }
        return (result == WAIT_OBJECT_0);
    }

    bool Waitable::test () const
    {
        return (wait(Timespan()));
    }

    Waitable::Set::Set ()
    {
        ::ZeroMemory(myData, sizeof(myData)), mySize = 0;
    }

    Waitable::Set::size_type Waitable::Set::capacity () const
    {
        return (MAXIMUM_WAIT_OBJECTS);
    }

    Waitable::Set::size_type Waitable::Set::size () const
    {
        return (mySize);
    }

    const Waitable::Set::value_type * Waitable::Set::data () const
    {
        return (myData);
    }

    Waitable::Set& Waitable::Set::remove (size_type i)
    {
        if (i < mySize) {
            std::copy(myData+i+1, myData+mySize, myData+i), --mySize;
        }
        return (*this);
    }

    Waitable::Set::value_type Waitable::Set::operator[] ( size_type i ) const
    {
        return (myData[i]);
    }

    Waitable::Set& Waitable::Set::operator|= ( value_type value )
    {
            // Fixed capacity, sorry!
        if (size() < capacity())
        {
            if ( std::find(begin(), end(), value) == end() ) {
                *end() = value, ++mySize;
            }
        }
        return (*this);
    }

    Waitable::Set& Waitable::Set::operator&= ( value_type value )
    {
        const iterator match = std::find(begin(), end(), value);
        if ( match != end() ) {
            std::copy(match+1, end(), match), --mySize;
        }
        return (*this);
    }

    bool Waitable::Set::operator& ( value_type value )
    {
        return (std::find(begin(), end(), value) != end());
    }

    Waitable::Set& Waitable::Set::operator|= ( const Waitable& object )
    {
        return ((*this) |= object.handle());
    }

    Waitable::Set& Waitable::Set::operator&= ( const Waitable& object )
    {
        return ((*this) &= object.handle());
    }

    bool Waitable::Set::operator& ( const Waitable& object )
    {
        return ((*this) & object.handle());
    }

}
