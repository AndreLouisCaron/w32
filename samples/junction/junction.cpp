// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.fs.hpp>
#include <iostream>
#include <string>

namespace {

    struct WrongArgumentCount : public std::exception {
        virtual const char * what () const throw() {
            return ("missing argument(s)");
        }
    };

    std::ostream& nothing ( std::ostream& out ) {
        out << "Nothing to do, use \"--usage\" for available options.";
        return (out);
    }

    std::ostream& version ( std::ostream& out ) {
        out << "\'junction\' for Microsoft Windows 2000, version 1.0";
        return (out);
    }

    std::ostream& usage ( std::ostream& out ) {
        out << "Usage: junction <target> <alias>" << std::endl
            << "  Creates a junction-point (hard-link to a directory)."
            << std::endl;
        return (out);
    }

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        if ( argc < 2 ) {
            std::cerr << nothing << std::endl;
            return (EXIT_FAILURE);
        }
        
        const w32::string option(argv[1]);
        if ( option == w32::string(L"--version") ) {
            std::cerr << version << std::endl;
            return (EXIT_FAILURE);
        }
        if ( option == w32::string(L"--help") ) {
            std::cerr << usage << std::endl;
            return (EXIT_FAILURE);
        }
        
        if ( argc != 3 ) {
            throw (WrongArgumentCount());
        }
        
        const w32::string target(argv[1]);
        const w32::string alias(argv[2]);
        w32::fs::junction(target,alias);
        return (EXIT_SUCCESS);
    }
}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.fs.lib" )
