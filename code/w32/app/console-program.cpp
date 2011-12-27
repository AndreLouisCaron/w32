// Copyright(c) Andre Caron, 2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Include this to obtain a linkage error when "run()" is missing.
#include <w32/app/console-program.hpp>

#include <w32.hpp>
#include <w32.dbg.hpp>
#include <exception>
#include <iostream>

int wmain ( int argc, wchar_t ** argv )
{
    try {
        w32::dbg::StructuredException::FilterReplacement filter;
        
        return (run(argc,argv));
    }
    catch ( const w32::Error& error ) {
        std::cerr << error << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( const w32::dbg::StructuredException& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( const std::exception& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
    catch ( ... ) {
        std::cerr << "Error: unknown exception!" << std::endl;
        return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}
