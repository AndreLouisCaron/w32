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

#include <w32.ipc/Processes.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ()
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Processes::Processes ()
        : Object(claim( ::snapshot() ))
    {
    }

    bool Processes::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Process32FirstW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Process32FirstW, error);
        }
        return (true);
    }

    bool Processes::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Process32NextW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Process32FirstW, error);
        }
        return (true);
    }

    Processes::Entry::Entry ()
    {
        clear();
    }

    Processes::Entry::Data& Processes::Entry::data ()
    {
        return (myData);
    }

    const Processes::Entry::Data& Processes::Entry::data () const
    {
        return (myData);
    }

    void Processes::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const Process Processes::Entry::self () const
    {
        return (Process(myData.th32ProcessID));
    }

    const Process Processes::Entry::parent () const
    {
        return (Process(myData.th32ParentProcessID));
    }

    const dword Processes::Entry::threads () const
    {
        return (myData.cntThreads);
    }

    const string Processes::Entry::executable () const
    {
        return (myData.szExeFile);
    }

} }
