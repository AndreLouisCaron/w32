// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/Stream.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace io {

    const Stream::Type Stream::Type::character ()
    {
        return (FILE_TYPE_CHAR);
    }

    const Stream::Type Stream::Type::disk ()
    {
        return (FILE_TYPE_DISK);
    }

    const Stream::Type Stream::Type::remote ()
    {
        return (FILE_TYPE_REMOTE);
    }

    const Stream::Type Stream::Type::ipc ()
    {
        return (FILE_TYPE_PIPE);
    }

    const Stream::Type Stream::Type::unknown ()
    {
        return (FILE_TYPE_UNKNOWN);
    }

    Stream::Type Stream::Type::of ( const Stream& stream )
    {
        const ::DWORD result = ::GetFileType(stream.handle());
        if ( result == FILE_TYPE_UNKNOWN ) {
            const ::DWORD error = ::GetLastError();
            if ( error != ERROR_SUCCESS ) {
                UNCHECKED_WIN32C_ERROR(GetFileType,error);
            }
        }
        return (Stream::Type(result));
    }

    Stream::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Stream::Stream ( const Handle& handle )
        : Object(handle)
    {
    }

    Stream::Size Stream::size () const
    {
        ::LARGE_INTEGER value = { 0 };
        const ::BOOL result = ::GetFileSizeEx(handle(),&value);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetFileSizeEx,::GetLastError());
        }
        return (Stream::Size(value));
    }

    Stream::Position Stream::position () const
    {
        ::LARGE_INTEGER distance = { 0 };
        ::LARGE_INTEGER value = { 0 };
        const ::BOOL result = ::SetFilePointerEx(
            handle(), distance, &value, FILE_CURRENT
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFilePointerEx,::GetLastError());
        }
        return (Stream::Position(value));
    }

    void Stream::position ( const Position& value ) const
    {
        const ::BOOL result = ::SetFilePointerEx(
            handle(), value.value(), 0, FILE_CURRENT
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetFilePointerEx,::GetLastError());
        }
    }

} }
