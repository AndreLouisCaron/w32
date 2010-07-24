// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/Changes.hpp>
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

    void Changes::next () const
    {
        const ::BOOL result = ::FindNextChangeNotification(handle());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FindNextChangeNotification,error);
        }
        
        // results with ReadDirectoryChangesW()...
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
