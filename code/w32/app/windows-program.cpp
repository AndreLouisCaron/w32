// Copyright(c) Andre Caron, 2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Include this to obtain a linkage error when "run()" is missing.
#include <w32/app/windows-program.hpp>

#include <w32.dbg.hpp>

#include <exception>
#include <iostream>
#include <cstdlib>

int __stdcall wWinMain
    ( ::HINSTANCE current, ::HINSTANCE, ::LPWSTR command, int show )
{
    try
    {
        w32::dbg::StructuredException::FilterReplacement filter;
        
        return (::run(command, show));
    }
    catch ( const w32::Error& error ) {
        w32::gdi::messagebox("Debug!",error.what());
        return (EXIT_FAILURE);
    }
    catch ( const w32::dbg::StructuredException& error ) {
        w32::gdi::messagebox("Debug!",error.what());
        return (EXIT_FAILURE);
    }
    catch ( const std::exception& error ) {
        w32::gdi::messagebox("Debug!",error.what());
        return (EXIT_FAILURE);
    }
    catch ( ... ) {
        w32::gdi::messagebox("Debug!","An unknown error occured.");
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
