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

#include <w32.mt/Thread.hpp>
#include <w32/Error.hpp>

namespace {

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

    ::HANDLE Thread::allocate
        ( ::LPTHREAD_START_ROUTINE function, ::LPVOID context )
    {
        ::DWORD identifier = 0;
        const ::HANDLE result = ::CreateThread(
            0, 0, function, context, 0, &identifier
            );
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateThread, error);
        }
        return (result);
    }


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
        : Object(Object::claim(allocate(function, parameter)))
    {
    }

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
    Thread::Identifier Thread::identifier () const
    {
        const ::DWORD identifier = ::GetThreadId(handle());
        if ( identifier == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetThreadId, error);
        }
        return (identifier);
    }
#endif

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
        Waitable(*this).wait();
    }

    bool Thread::join ( const Timespan& timeout ) const
    {
        return (Waitable(*this).wait(timeout));
    }

    Thread::operator Waitable () const
    {
        return Waitable(handle());
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
