// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

}
