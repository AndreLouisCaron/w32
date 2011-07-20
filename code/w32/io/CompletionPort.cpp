// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/CompletionPort.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::DWORD threads, ::HANDLE stream, ::ULONG_PTR key )
    {
        const ::HANDLE result =
            ::CreateIoCompletionPort(stream, 0, key, threads);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateIoCompletionPort, error);
        }
        return (result);
    }

    ::HANDLE allocate ( ::DWORD threads )
    {
        return (allocate(threads, INVALID_HANDLE_VALUE, 0));
    }

}

namespace w32 { namespace io {

    CompletionPort::CompletionPort ( dword threads )
        : Object(claim( ::allocate(threads) ))
    {
    }

    CompletionPort::CompletionPort
        ( const Stream& stream, Key key, dword threads )
        : Object(claim( ::allocate(threads, stream.handle(), key) ))
    {
    }

    void CompletionPort::bind ( const Stream& stream, Key key )
    {
        const ::HANDLE result = ::CreateIoCompletionPort
            (stream.handle(), handle(), key, 0);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateIoCompletionPort, error);
        }
    }

    void CompletionPort::bind ( const Stream& stream, void * key )
    {
        bind(stream, reinterpret_cast<Key>(key));
    }

    void CompletionPort::get ( Size& bytes, Key& key, Transfer *& transfer )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &key,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), INFINITE
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        ))
            {
                bytes = 0; key = 0; transfer = 0; return;
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
    }

    bool CompletionPort::get
        ( Size& bytes, Key& key, Transfer *& transfer, Timespan timeout )
    {
        const ::BOOL result = ::GetQueuedCompletionStatus(
            handle(), &bytes, &key,
            &reinterpret_cast<::OVERLAPPED*&>(transfer), timeout.ticks()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            //if ( error != !?WHAT_IS_THE_TIMEOUT_CODE?! ) {}
            if ((error == ERROR_NETNAME_DELETED   )||
                (error == ERROR_CONNECTION_ABORTED)||
                (error == ERROR_HANDLE_EOF        ))
            {
                bytes = 0; key = 0; transfer = 0; return (true);
            }
            UNCHECKED_WIN32C_ERROR(GetQueuedCompletionStatus, error);
        }
        return (result == TRUE);
    }

    void CompletionPort::put ( Size bytes, Key key, Transfer * transfer )
    {
        const ::BOOL result = ::PostQueuedCompletionStatus
            (handle(), bytes, key, reinterpret_cast<::OVERLAPPED*>(transfer));
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(PostQueuedCompletionStatus, error);
        }
    }

} }
