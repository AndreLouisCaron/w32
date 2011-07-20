// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/sc/Database.hpp>
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
