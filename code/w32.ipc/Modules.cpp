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

#include <w32.ipc/Modules.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ( ::DWORD process )
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Modules::Modules ( Process::Identifier process )
        : Object(claim( ::snapshot(process) ))
    {
    }

    Modules::Modules ( const Process& process )
        : Object(claim( ::snapshot(process.identifier()) ))
    {
    }

    bool Modules::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Module32FirstW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Module32FirstW, error);
        }
        return (true);
    }

    bool Modules::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Module32NextW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Module32FirstW, error);
        }
        return (true);
    }

    Modules::Entry::Entry ()
    {
        clear();
    }

    Modules::Entry::Data& Modules::Entry::data ()
    {
        return (myData);
    }

    const Modules::Entry::Data& Modules::Entry::data () const
    {
        return (myData);
    }

    void Modules::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const pointer Modules::Entry::base () const
    {
        return (myData.modBaseAddr);
    }

    const string Modules::Entry::name () const
    {
        return (myData.szModule);
    }

    const string Modules::Entry::path () const
    {
        return (myData.szExePath);
    }

} }
