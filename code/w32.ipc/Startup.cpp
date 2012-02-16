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

#include <w32.ipc/Startup.hpp>
#include <w32.ipc/Process.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/OutputStream.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace ipc {

    Startup::Startup ()
        : myFlags(0), myInherit(FALSE), myState(0)
    {
        myFlags |= CREATE_UNICODE_ENVIRONMENT;
    }

    Startup& Startup::program ( const string& path )
    {
        myProgram = path;
        return (*this);
    }

    Startup& Startup::location ( const string& path )
    {
        myLocation = path;
        return (*this);
    }

    Startup& Startup::command ( const string& command )
    {
        myCommand = command;
        return (*this);
    }

    Startup& Startup::clear_environment ()
    {
        myEnvironment.clear();
        return (*this);
    }

    Startup& Startup::inherit_environment ()
    {
        return (inherit_environment(w32::Environment()));
    }

    Startup& Startup::inherit_environment
        ( const w32::Environment::Map& environment )
    {
        myEnvironment.insert(environment.begin(), environment.end());
        return (*this);
    }

    Startup& Startup::add_to_environment
        ( const string& field, const string& value )
    {
        myEnvironment.insert(std::make_pair(field, value));
        return (*this);
    }

    Startup& Startup::breakawayFromJob ()
    {
        myFlags |= CREATE_BREAKAWAY_FROM_JOB;
        return (*this);
    }

    Startup& Startup::defaultErrorMode ()
    {
        myFlags |= CREATE_DEFAULT_ERROR_MODE;
        return (*this);
    }

    Startup& Startup::newConsole ()
    {
        myFlags |= CREATE_NEW_CONSOLE;
        return (*this);
    }

    Startup& Startup::newProcessGroup ()
    {
        myFlags |= CREATE_NEW_PROCESS_GROUP;
        return (*this);
    }

    Startup& Startup::noWindow ()
    {
        myFlags |= CREATE_NO_WINDOW;
        return (*this);
    }

    Startup& Startup::protectedProcess ()
    {
        myFlags |= CREATE_PROTECTED_PROCESS;
        return (*this);
    }

    Startup& Startup::preserveCodeAuthorizationLevel ()
    {
        myFlags |= CREATE_PRESERVE_CODE_AUTHZ_LEVEL;
        return (*this);
    }

    Startup& Startup::suspended ()
    {
        myFlags |= CREATE_SUSPENDED;
        return (*this);
    }

    Startup& Startup::debugOnlyThisProcess ()
    {
        myFlags |= DEBUG_ONLY_THIS_PROCESS;
        return (*this);
    }

    Startup& Startup::debugThisProcessTree ()
    {
        myFlags |= DEBUG_PROCESS;
        return (*this);
    }

    Startup& Startup::detachedProcess ()
    {
        myFlags |= DETACHED_PROCESS;
        return (*this);
    }

    Startup& Startup::inheritHandles ()
    {
        myInherit = true;
        return (*this);
    }

    Startup& Startup::stdi ( io::InputStream stream )
    {
        myStdi = stream.handle();
        myState |= STARTF_USESTDHANDLES;
        return (inheritHandles());
    }

    Startup& Startup::stdo ( io::OutputStream stream )
    {
        myStdo = stream.handle();
        myState |= STARTF_USESTDHANDLES;
        return (inheritHandles());
    }

    Startup& Startup::stde ( io::OutputStream stream )
    {
        myStde = stream.handle();
        myState |= STARTF_USESTDHANDLES;
        return (inheritHandles());
    }

    Startup& Startup::desktop ( const string& name )
    {
        myDesktop = name;
        return (*this);
    }

    Startup& Startup::title ( const string& text )
    {
        myTitle = text;
        return (*this);
    }

    Startup& Startup::position ( dword x, dword y )
    {
        myState |= STARTF_USEPOSITION;
        myX = x;
        myY = y;
        return (*this);
    }

    Startup& Startup::size ( dword width, dword height )
    {
        myState |= STARTF_USESIZE;
        myWidth  = width;
        myHeight = height;
        return (*this);
    }

    Startup& Startup::showWindow ( word command )
    {
        myState |= STARTF_USESHOWWINDOW;
        myShowCommand = command;
        return (*this);
    }

    Process Startup::spawn () const
    {
        // Translate process startup information.
        ::STARTUPINFOW startup;
        ::ZeroMemory(&startup, sizeof(startup));
        startup.cb         = sizeof(startup);
        startup.dwFlags    = myState;
        startup.dwX        = myX;
        startup.dwY        = myY;
        startup.dwXSize    = myWidth;
        startup.dwYSize    = myHeight;
        startup.hStdInput  = myStdi;
        startup.hStdOutput = myStdo;
        startup.hStdError  = myStde;
        string cmdline(myCommand);
        const ::LPCWSTR program = myProgram.empty()? 0 : myProgram.data();
        const ::LPWSTR command = cmdline.empty()? 0 : cmdline.data();
        const ::LPCWSTR location = myLocation.empty()? 0 : myLocation.data();
        w32::string environment = w32::Environment::format(myEnvironment);
        // Ask the system to spawn the new process.
        ::PROCESS_INFORMATION process;
        ::ZeroMemory(&process, sizeof(process));
        const ::BOOL result = ::CreateProcessW(
             program, command, 0, 0, myInherit, myFlags,
             environment.data(), location, &startup, &process);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateProcess, error);
        }
        // Return a nice wrapper object for the new handle.
        ::CloseHandle(process.hThread);
        return (Process(Object::claim(process.hProcess)));
    }

} }
