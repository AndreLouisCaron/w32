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

// NOTE: make sure to statically link with **everything**!
// NOTE: to build in DEBUG mode, you need to compile Python!

#include <w32.hpp>
#include <w32.msi.hpp>

// Enable logging:
//   [HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows\Installer]
//   "Debug"=dword:00000003
//   "Logging"="vicewarmup"

namespace {

#if 0
    void log ( w32::msi::Install, const w32::string& message )
    {
        w32::msi::Record record(1);
        record.set(0, message.data());
        install.process(INSTALLMESSAGE(INSTALLMESSAGE_INFO), record);
    }
    void user ( w32::msi::Install, const w32::string& message, w32::dword flags=0 )
    {
        w32::msi::Record record(1);
        record.set(0, message.data());
        install.process(INSTALLMESSAGE(INSTALLMESSAGE_USER+flags), record);
    }
#endif

}

extern "C" {

    int __stdcall DllMain ( ::HANDLE module, ::DWORD reason, ::LPVOID )
    try
    {
            // "dll" constructor: return "FALSE" to abort.
        if ( reason == DLL_PROCESS_ATTACH )
        {
        }
            // "dll" destructor: always return "TRUE"!
        if ( reason == DLL_PROCESS_DETACH )
        try
        {
        }
            // Neutralize all errors, we should never prevent unloading!
        catch ( ... ) {}
        
        return (TRUE);
    }
    catch ( ... )
    {
        return (FALSE);
    }

        // Name this whatever you want.
    w32::uint __stdcall run ( ::MSIHANDLE module )
    try
    {
        // Use ::MsiGetProperty() to fetch external settings.
        
        return (ERROR_SUCCESS);
    }
    catch ( ... )
    {
        return (EXIT_FAILURE);
    }

}
