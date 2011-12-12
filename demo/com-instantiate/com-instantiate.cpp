// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.com.hpp>
#include <sstream>

namespace {

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    try
    {
    const w32::com::Library _;
        
            // Parse the requested object uuid.
        if ( argc < 2 )
        {
            std::cerr
                << "What object?" << std::endl;
            return (EXIT_FAILURE);
        }
        std::wistringstream input(argv[1]);
        w32::com::Guid guid;
        if ( !(input >> guid) )
        {
            std::cerr
                << "Expecting an object GUID!" << std::endl;
            return (EXIT_FAILURE);
        }
        std::wcerr << guid << std::endl;
        
            // Create an instance of the requested type.
        const w32::com::Ptr< ::IUnknown > instance
            = w32::com::instantiate(guid);
        
        return (EXIT_SUCCESS);
    }
    catch ( const w32::com::Error& error )
    {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/app/console-program.cpp>
