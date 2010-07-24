// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/Thread.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::LPTHREAD_START_ROUTINE function, ::LPVOID parameter )
    {
        ::DWORD identifier = 0;
        const ::HANDLE result = ::CreateThread(
            0, 0, function, parameter, 0, &identifier
            );
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThread, error);
        }
        return (result);
    }

    ::HANDLE find ( ::DWORD id )
    {
        const ::HANDLE result = ::OpenThread(
            THREAD_ALL_ACCESS, FALSE, id
            );
        if ( result == NULL ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(OpenThread, error);
        }
        return (result);
    }

}

namespace w32 { namespace mt {

    Thread Thread::current ()
    {
        const Handle handle(proxy(::GetCurrentThread()));
        return (Thread(handle));
    }

    Thread Thread::open ( Identifier identifier )
    {
        const Handle handle(claim(::find(identifier)));
        return (Thread(handle));
    }

    Thread::Thread ( const Handle& handle )
        : Object(handle)
    {
    }

    Thread::Thread ( Function function, Parameter parameter )
        : Object(Object::claim(::allocate(function, parameter)))
    {
    }

    Thread::Identifier Thread::identifier () const
    {
        const ::DWORD identifier = ::GetThreadId(handle());
        if ( identifier == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetThreadId, error);
        }
        return (identifier);
    }

    void Thread::priority ( const Priority& priority )
    {
        const ::BOOL result = ::SetThreadPriority(
            handle(), priority.value()
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetThreadPriority, error);
        }
    }

    void Thread::terminate ( dword status )
    {
        const ::BOOL result = ::TerminateThread(handle(),status);
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(TerminateThread, error);
        }
    }

    dword Thread::status () const
    {
        ::DWORD value = 0;
        const ::BOOL result = ::GetExitCodeThread(handle(),&value);
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetExitCodeThread, error);
        }
        return (value);
    }

    bool Thread::alive () const
    {
        return (status() == STILL_ACTIVE);
    }

    dword Thread::suspend ()
    {
        const ::DWORD count = ::SuspendThread(handle());
        if ( count == static_cast<::DWORD>(-1) )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SuspendThread, error);
        }
        return (count);
    }

    dword Thread::resume ()
    {
        const ::DWORD count = ::ResumeThread(handle());
        if ( count == static_cast<::DWORD>(-1) )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ResumeThread, error);
        }
        return (count);
    }

    void Thread::join () const
    {
        wait();
    }

    bool Thread::join ( const Timespan& timeout ) const
    {
        return (wait(timeout));
    }

    void sleep ( const Timespan& timespan )
    {
        ::Sleep(timespan.ticks());
    }

    bool alertable ( const Timespan& timespan )
    {
        return (::SleepEx(timespan.ticks(),TRUE) == WAIT_IO_COMPLETION);
    }

    const Thread::Priority Thread::Priority::idle ()
    {
        return (THREAD_PRIORITY_IDLE);
    }

    const Thread::Priority Thread::Priority::lowest ()
    {
        return (THREAD_PRIORITY_LOWEST);
    }

    const Thread::Priority Thread::Priority::lower ()
    {
        return (THREAD_PRIORITY_BELOW_NORMAL);
    }

    const Thread::Priority Thread::Priority::normal ()
    {
        return (THREAD_PRIORITY_NORMAL);
    }

    const Thread::Priority Thread::Priority::higher ()
    {
        return (THREAD_PRIORITY_ABOVE_NORMAL);
    }

    const Thread::Priority Thread::Priority::highest ()
    {
        return (THREAD_PRIORITY_HIGHEST);
    }

    const Thread::Priority Thread::Priority::critical ()
    {
        return (THREAD_PRIORITY_TIME_CRITICAL);
    }

    Thread::Priority::Priority ( Value value )
        : myValue(value)
    {
    }

    Thread::Priority::Value Thread::Priority::value () const
    {
        return (myValue);
    }

    Thread::Priority::operator Thread::Priority::Value () const
    {
        return (value());
    }

    void yield ()
    {
            // If there are no other threads, this does nothing.
        ::SwitchToThread();
    }

    void exit ( dword code )
    {
        ::ExitThread(code);
    }

} }
