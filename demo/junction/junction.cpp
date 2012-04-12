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

#include <w32/app/console-program.hpp>

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

#include <w32/app/console-program.cpp>
