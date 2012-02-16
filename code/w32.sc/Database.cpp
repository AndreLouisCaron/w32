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

#include <w32.sc/Database.hpp>
#include <w32/Error.hpp>

namespace {

    ::SC_HANDLE open ( ::LPCWSTR database, ::DWORD access )
    {
        const ::SC_HANDLE manager = ::OpenSCManagerW(0,database,access);
        if ( manager == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ACCESS_DENIED ) {
            }
            UNCHECKED_WIN32C_ERROR(OpenSCManager,error);
        }
        return (manager);
    }

    void execute ( ::LPCWSTR name, ::LPSERVICE_MAIN_FUNCTIONW context )
    {
        const ::SERVICE_TABLE_ENTRYW services[2] = {
            { const_cast<wchar_t*>(name), context }, { 0, 0 }
        };
        
        if ( ::StartServiceCtrlDispatcherW(services) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT ) {
            }
            else if ( error == ERROR_SERVICE_ALREADY_RUNNING ) {
            }
            UNCHECKED_WIN32C_ERROR(StartServiceCtrlDispatcher,error);
        }
    }

}

namespace w32 { namespace sc {

    Database::Database ()
        : Object(claim(open(SERVICES_ACTIVE_DATABASEW,SC_MANAGER_ALL_ACCESS)))
    {
    }

    void Database::run ( const string& service, Service::Context context )
    {
        ::execute(service.c_str(), context);
    }

} }
