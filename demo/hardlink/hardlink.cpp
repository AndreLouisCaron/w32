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

    std::ostream & nothing ( std::ostream & out ) {
        out << "Nothing to do, use \"--help\" for available options.";
        return (out);
    }

    std::ostream & missing ( std::ostream & out ) {
        out << "Missing argument(s), use \"--help\" for available options.";
        return (out);
    }

    std::ostream & invalid ( std::ostream & out ) {
        out << "Invalid argument(s), use \"--help\" for available options.";
        return (out);
    }

    std::ostream & ignored ( std::ostream & out ) {
        out << "Extra trailing argument(s) ignored.";
        return (out);
    }

    std::ostream & version ( std::ostream & out ) {
        out << "\'hardlink\' for Microsoft Windows 2000, version 1.0";
        return (out);
    }

    std::ostream & description ( std::ostream & out ) {
        out << "This program is used for creating hardlinks on Windows 2000. "
            << "Hardlinks are basically names for files. When a new file is "
            << "created, the file's name is a hardlink to the file. If you "
            << "create a new hardlink to that same file, then you can use "
            << "either hardlink to access the same storage space. Deleting the "
            << "file will remove the selected hardlink, and the storage space "
            << "is returned to the disk when no more hardlinks exist."
            << std::endl;
        return (out);
    }

    std::ostream & usage ( std::ostream & out ) {
        out << "Usage:" << std::endl
            << "   hardlink \'option\' [target] [link]" << std::endl << std::endl
            << "   Options:" << std::endl
            << "      -m[a]k[e] : make a new hardlink. \'target\' must be the "
            << "path to an existing file and \'link\' must be the destination "
            << "path for the new link(no file should exist there)." << std::endl
            << "      --u[sage] : print this help." << std::endl
            << "      --v[ersion] : print program version."
            << "Notes:" << std::endl
            << "   To remove a hardlink, simply delete the file using the link"
            << "\'s name. If that was the last hardlink, the actual file will "
            << "be deleted.";
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
        w32::fs::hardlink(target,alias);
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
