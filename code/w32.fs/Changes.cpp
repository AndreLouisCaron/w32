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

#include <w32.fs/Changes.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HANDLE find ( const wchar_t * path, ::DWORD filter, bool recursive )
    {
        const ::HANDLE result = ::FindFirstChangeNotificationW(
            path, recursive? TRUE : FALSE, filter
            );
        if ( result == INVALID_HANDLE_VALUE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FindFirstChangeNotification, error);
        }
        return (result);
    }

    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::FindCloseChangeNotification(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace fs {

    Changes::Changes
        ( const string& path, const Filter& filter, bool recursive )
        : Object(Handle(
              ::find(path.data(), filter.value(), recursive), &::release
              ))
    {
    }

    Changes::Changes ( const Handle& handle )
        : Object(handle)
    {
    }

    void Changes::wait () const
    {
        return (Waitable(*this).wait());
    }

    bool Changes::wait (w32::Timespan timeout) const
    {
        return (Waitable(*this).wait(timeout));
    }

    void Changes::next ()
    {
        const ::BOOL result = ::FindNextChangeNotification(handle());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FindNextChangeNotification,error);
        }
        
        // results with ReadDirectoryChangesW()...
    }

    Changes::operator Waitable () const
    {
        return Waitable(handle());
    }

    const Changes::Filter Changes::Filter::filename ()
    {
        return (FILE_NOTIFY_CHANGE_FILE_NAME);
    }

    const Changes::Filter Changes::Filter::foldername ()
    {
        return (FILE_NOTIFY_CHANGE_DIR_NAME);
    }

    const Changes::Filter Changes::Filter::attributes ()
    {
        return (FILE_NOTIFY_CHANGE_ATTRIBUTES);
    }

    const Changes::Filter Changes::Filter::size ()
    {
        return (FILE_NOTIFY_CHANGE_SIZE);
    }

    const Changes::Filter Changes::Filter::lastwrite ()
    {
        return (FILE_NOTIFY_CHANGE_LAST_WRITE);
    }

    const Changes::Filter Changes::Filter::security ()
    {
        return (FILE_NOTIFY_CHANGE_SECURITY);
    }

    const Changes::Filter Changes::Filter::all ()
    {
        return (FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_ATTRIBUTES |
            FILE_NOTIFY_CHANGE_LAST_WRITE |
            FILE_NOTIFY_CHANGE_SECURITY
            );
    }

    Changes::Filter::Filter ( Value value )
        : myValue(value)
    {
    }

    Changes::Filter::Value Changes::Filter::value () const
    {
        return (myValue);
    }

    Changes::Filter& Changes::Filter::operator|= ( const Filter& other )
    {
        myValue |= other.myValue;
        return (*this);
    }

    Changes::Filter Changes::Filter::operator| ( const Filter& other ) const
    {
        Filter result(*this);
        result |= other;
        return (result);
    }

    Changes::Filter& Changes::Filter::operator&= ( const Filter& other )
    {
        myValue &= other.myValue;
        return (*this);
    }

    Changes::Filter Changes::Filter::operator& ( const Filter& other ) const
    {
        Filter result(*this);
        result &= other;
        return (result);
    }

} }
