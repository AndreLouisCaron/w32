// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.ipc.hpp>

namespace {

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Choose some process to list modules from.
        const w32::ipc::Process process =
            w32::ipc::Process::current();
        
            // List modules loaded in that process.
        w32::ipc::Modules modules(process);
        w32::ipc::Modules::Entry module;
        if ( modules.find(module) )
        {
            do {
                std::wcerr << module.path() << std::endl;
            }
            while ( modules.next(module) );
        }
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.ipc.lib" )
