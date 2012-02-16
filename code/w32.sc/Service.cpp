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

#include <w32.sc/Service.hpp>
#include <w32.sc/Database.hpp>
#include <w32/Error.hpp>

namespace {

    ::DWORD __stdcall ControlHandlerCallback (
        ::DWORD event, ::DWORD type, ::LPVOID data, ::LPVOID context
    )
    {
        // Note: "type" parameter is only used for services that register for
        // device events, hardware profile notifications, power events and
        // session change events. "data" parameters are also sometimes used in
        // these circumstances.
        
            // Fetch the service status handler from generic callback argument.
        volatile w32::sc::Service::Handler& handler
            = *static_cast< w32::sc::Service::Handler* >(context);
         
            // Dispatch reaction depending on event type.
        switch ( event )
        {
            // The SCM wants to know how we are doing, give it our latest state.
        case SERVICE_CONTROL_INTERROGATE: {
            handler.signal();
            } break;
         
            // The SCM asked us to stop, make sure we do just that.
            // NOTE: this just tells the client code to stop, the final
            // status will be signaled will be done in the object's
            // destructor is called (when the service is actually done).
        case SERVICE_CONTROL_PRESHUTDOWN:
        case SERVICE_CONTROL_SHUTDOWN:
        case SERVICE_CONTROL_STOP: {
            handler.stop();
            } break;
         
        case SERVICE_CONTROL_CONTINUE: {
            handler.resume();
            } break;
         
        case SERVICE_CONTROL_PAUSE: {
            handler.pause();
            } break;
         
            // Can't happen but is foolproof and makes the compiler shut up.
        default: {
            return (ERROR_CALL_NOT_IMPLEMENTED);
            }
        }
         
        return (NO_ERROR);
    }

    ::SERVICE_STATUS_HANDLE register_ ( ::LPCWSTR service, ::LPVOID data )
    {
        ::SERVICE_STATUS_HANDLE handle = ::RegisterServiceCtrlHandlerExW(
                                             service, &ControlHandlerCallback, data
                                         );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_SERVICE_DOES_NOT_EXIST ) {
            }
            UNCHECKED_WIN32C_ERROR(RegisterServiceCtrlHandlerEx,error);
        }
        return (handle);
    }

    ::SC_HANDLE create ( ::SC_HANDLE database, ::LPCWSTR name, ::LPCWSTR path )
    {
        const ::SC_HANDLE service = ::CreateServiceW(
            database, name, 0, SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
            SERVICE_AUTO_START, SERVICE_ERROR_IGNORE, path, 0, 0, 0, 0, 0
            );
        if ( service == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_SERVICE_EXISTS ) {
            }
            else if ( error == ERROR_DUPLICATE_SERVICE_NAME ) {
            }
            UNCHECKED_WIN32C_ERROR(CreateService,error);
        }
        return (service);
    }

    ::SC_HANDLE open (
        ::SC_HANDLE manager, ::LPCWSTR name, ::DWORD access
    )
    {
        const ::SC_HANDLE service = ::OpenServiceW(manager,name,access);
        if ( service == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ACCESS_DENIED ) {
            }
            else if ( error == ERROR_SERVICE_DOES_NOT_EXIST ) {
            }
            UNCHECKED_WIN32C_ERROR(OpenService,error);
        }
        return (service);
    }

}

namespace w32 { namespace sc {

    Service::Service (
        Database& database, const string& name, const string& path
        )
        : Object(claim(::create(
              database.handle(), name.c_str(), path.c_str()
              )))
    {
    }

    Service::Service ( Database& database, const string& name )
        : Object(claim(::open(
              database.handle(), name.c_str(), SERVICE_ALL_ACCESS
          )))
    {
    }

    void Service::remove ()
    {
        if ( ::DeleteService(handle()) == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ACCESS_DENIED ) {
            }
                // Ignore "already marker for delete" cases.
            else if ( error != ERROR_SERVICE_MARKED_FOR_DELETE ) {
                UNCHECKED_WIN32C_ERROR(DeleteService,error);
            }
        }
    }

    const Service::Status Service::Status::stopped(SERVICE_STOPPED);
    const Service::Status Service::Status::starting(SERVICE_START_PENDING);
    const Service::Status Service::Status::stopping(SERVICE_STOP_PENDING);
    const Service::Status Service::Status::running(SERVICE_RUNNING);
    const Service::Status Service::Status::resuming(SERVICE_CONTINUE_PENDING);
    const Service::Status Service::Status::pausing(SERVICE_PAUSE_PENDING);
    const Service::Status Service::Status::paused(SERVICE_PAUSED);

    Service::Status::Status ( Value value )
        : myValue(value)
    {
    }

    Service::Status::Value Service::Status::value () const
    {
        return (myValue);
    }

    bool Service::Status::operator== ( const Status& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Service::Status::operator!= ( const Status& other ) const
    {
        return (myValue != other.myValue);
    }

    Service::Handler::Handler ( const string &service )
        : myHandle(0)
    {
        myHandle = register_(service.c_str(),this);
        
            // Initialize default state.
        ::ZeroMemory(&myValue,sizeof(myValue));
        myValue.dwServiceType      = SERVICE_WIN32_OWN_PROCESS;
        myValue.dwControlsAccepted = SERVICE_ACCEPT_STOP;
        myValue.dwWin32ExitCode    = NO_ERROR;
        myValue.dwCurrentState     = SERVICE_RUNNING;
        
            // Tell the SCM the service is up and running.
        signal(Status::running);
    }

    Service::Handler::~Handler ()
    {
            // Tell the SCM the service has finally stopped.
        signal(Status::stopped);
    }

    void Service::Handler::signal () const volatile
    {
        const ::BOOL result = ::SetServiceStatus(
            myHandle, const_cast<::SERVICE_STATUS*>(&myValue)
            );
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetServiceStatus,::GetLastError());
        }
    }

    void Service::Handler::signal ( const Status& status ) volatile
    {
        myValue.dwCurrentState = status.value();
        signal();
    }

    Service::Status Service::Handler::current () const volatile
    {
        Service::Status status = Service::Status::stopped;
        
        switch ( myValue.dwCurrentState )
        {
        case SERVICE_STOPPED: {
            status = Service::Status::stopped;
            } break;

        case SERVICE_START_PENDING: {
            status = Service::Status::starting;
            } break;

        case SERVICE_STOP_PENDING: {
            status = Service::Status::stopping;
            } break;

        case SERVICE_RUNNING: {
            status = Service::Status::running;
        } break;

        case SERVICE_CONTINUE_PENDING: {
            status = Service::Status::resuming;
            } break;

        case SERVICE_PAUSE_PENDING: {
            status = Service::Status::pausing;
            } break;

        case SERVICE_PAUSED: {
            status = Service::Status::paused;
            } break;

        default: {}
        }
        
        return (status);
    }

    void Service::Handler::exit ( dword code ) volatile
    {
        myValue.dwWin32ExitCode = code;
    }

    void Service::Handler::stop () volatile
    {
            // Pass status to service.
        signal(Status::stopping);
    }

    void Service::Handler::pause () volatile
    {
        signal(Status::paused);
    }

    void Service::Handler::resume () volatile
    {
        signal(Status::running);
    }

    void Service::Handler::control ( int code ) volatile
    {
    }

} }
