// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

// NOTE: make sure to statically link with **everything**!
// NOTE: to build in DEBUG mode, you need to compile Python!

#include <w32.hpp>
#include <w32.msi.hpp>
#include <Python.h>

// Enable logging:
//   [HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows\Installer]
//   "Debug"=dword:00000003
//   "Logging"="vicewarmup"

namespace {

        // Sample python script!
    const char script[] = ""
        "import os\n"
        "print os.listdir('.')"
        ;

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
        
            // Setup the interpreter.
        ::Py_Initialize();
        
            // Run the custom script.
        ::PyRun_SimpleString(::script);
        
            //  Cleanup the interpreter.
        ::Py_Finalize();
        return (ERROR_SUCCESS);
    }
    catch ( ... )
    {
        ::Py_Finalize();
        return (EXIT_FAILURE);
    }

}
