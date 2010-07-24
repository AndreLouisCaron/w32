// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/dbg/Log.hpp>
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
