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

#include <w32.dbg/Log.hpp>
#include <w32/Error.hpp>
#include <w32.rgs.hpp>
#include <iostream>

namespace {

    ::HANDLE open ( ::LPCWSTR source )
    {
        const ::HANDLE result = ::RegisterEventSourceW(0, source);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RegisterEventSource, error);
        }
        return (result);
    }

    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::DeregisterEventSource(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HANDLE )
    {
    }

        // Registry key, under HKEY_LOCAL_MACHINE, where logs are installed.
    w32::rgs::Key sources ()
    {
        const ::WCHAR root[] =
            L"SYSTEM\\CurrentControlSet\\Services\\Log\\Application";
        return (w32::rgs::Key(w32::rgs::Key::machine(), root));
    }

    const ::DWORD all =
        EVENTLOG_SUCCESS
        | EVENTLOG_ERROR_TYPE
        | EVENTLOG_WARNING_TYPE
        | EVENTLOG_INFORMATION_TYPE
        | EVENTLOG_AUDIT_SUCCESS
        | EVENTLOG_AUDIT_FAILURE
        ;

}

namespace w32 { namespace dbg {

    Log::Handle Log::claim ( ::HANDLE object )
    {
        return (Handle(object, &release));
    }

    Log::Handle Log::proxy ( ::HANDLE object )
    {
        return (Handle(object, &abandon));
    }

    void Log::install (
        const string& name, const string& path,
        const string& categories, dword count )
    {
        rgs::Key log = rgs::Key::create(::sources(), name);
        rgs::Value(log,"EventMessageFile") = path;
        rgs::Value(log,"CategoryCount") = count;
        rgs::Value(log,"CategoryMessageFile") = categories;
        rgs::Value(log,"TypesSupported") = ::all;
    }

    void Log::remove ( const string& name )
    {
        ::sources().delete_(name);
    }

    Log::Log ( const string& name )
        : myHandle(claim(::open(name.c_str())))
    {
    }

    Log::Log ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Log::Handle& Log::handle () const
    {
        return (myHandle);
    }

    void Log::report ( const Event& event )
    {
        const ::BOOL result = ::ReportEventW(
            handle(), event.type().value(), event.category(),
            event.message(), 0, event.argc(), 0, event.argv(), 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ReportEvent, error);
        }
    }

} }
