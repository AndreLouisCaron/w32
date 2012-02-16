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

#include <w32.ipc/Threads.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ()
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Threads::Threads ()
        : Object(claim( ::snapshot() ))
    {
    }

    bool Threads::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Thread32First(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Thread32First, error);
        }
        return (true);
    }

    bool Threads::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Thread32Next(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Thread32First, error);
        }
        return (true);
    }

    Threads::Entry::Entry ()
    {
        clear();
    }

    Threads::Entry::Data& Threads::Entry::data ()
    {
        return (myData);
    }

    const Threads::Entry::Data& Threads::Entry::data () const
    {
        return (myData);
    }

    void Threads::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const mt::Thread Threads::Entry::self () const
    {
        return (mt::Thread::open(myData.th32ThreadID));
    }

    const Process Threads::Entry::process () const
    {
        return (Process(myData.th32OwnerProcessID));
    }

} }
