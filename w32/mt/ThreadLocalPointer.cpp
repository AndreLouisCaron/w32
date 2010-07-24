// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/ThreadLocalPointer.hpp>
#include <w32/Error.hpp>

namespace {

    ::DWORD allocate ()
    {
        const ::DWORD handle = ::TlsAlloc();
        if ( handle == TLS_OUT_OF_INDEXES )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TlsAlloc, error);
        }
        return (handle);
    }

}

namespace w32 { namespace mt {

    ThreadLocalPointer::Handle::Handle ( Value value )
        : myValue(value)
    {
    }

    ThreadLocalPointer::Handle::~Handle ()
    {
        if ( ok() && (::TlsFree(myValue) == FALSE) ) {
            UNCHECKED_WIN32C_ERROR(TlsFree,::GetLastError());
        }
    }

    bool ThreadLocalPointer::Handle::bad () const
    {
        return (myValue == TLS_OUT_OF_INDEXES);
    }

    bool ThreadLocalPointer::Handle::ok () const
    {
        return (myValue != TLS_OUT_OF_INDEXES);
    }

    ThreadLocalPointer::Handle::Value
        ThreadLocalPointer::Handle::value () const
    {
        return (myValue);
    }

    ThreadLocalPointer::ThreadLocalPointer ()
        : myHandle(allocate())
    {
    }

    const ThreadLocalPointer::Handle& ThreadLocalPointer::handle () const
    {
        return (myHandle);
    }

    void * ThreadLocalPointer::get () const
    {
        return (::TlsGetValue(handle().value()));
    }

    void ThreadLocalPointer::set ( void * value )
    {
        const ::BOOL result = ::TlsSetValue(handle().value(), value);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TlsSetValue, error);
        }
    }

    ThreadLocalPointer& ThreadLocalPointer::operator= ( void * value )
    {
        set(value);
        return (*this);
    }

    ThreadLocalPointer::operator void* () const
    {
        return (get());
    }

} }
