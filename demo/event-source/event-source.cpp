// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.dbg.hpp>
#include <w32.rgs.hpp>
#include <exception>
#include <iostream>
#include <sstream>

namespace {

    struct WrongArgumentCount : public std::exception {
        virtual const char * what () const throw() {
            return ("wrong number of arguments");
        }
    };

    struct InvalidOption : public std::exception {
        virtual const char * what () const throw() {
            return ("invalid option");
        }
    };

    struct NotANumber : public std::exception {
        virtual const char * what () const throw() {
            return ("expected a number");
        }
    };

    std::ostream& program ( std::ostream& out ) {
        return (out << "event-source");
    }

    std::ostream& author ( std::ostream& out ) {
        return (out << "Andre Louis Caron");
    }

    std::ostream& copyright ( std::ostream& out )
    {
        out << "Copyright (c) " << author << " 2008.";
        return (out);
    }

    std::ostream& disclaimer ( std::ostream& out )
    {
        out << "This is free software; see the source for copying conditions."
            << " There is NO" << std::endl << "warranty; not even for "
            << "MECHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.";
        return (out);
    }

    std::ostream& version ( std::ostream& out )
    {
        static const int major = 1;
        static const int minor = 0;
        out << program << " (" << major << '.' << minor << ')' << std::endl
            << "Written by " << author << '.' << std::endl
            << std::endl
            << copyright << std::endl
            << disclaimer;
        return (out);
    }

    std::ostream& usage ( std::ostream& out )
    {
        out << "Usage: event-source <option> [ arguments... ]"
            << std::endl
            << "Installs or removes an application as event source."
            << std::endl
            << std::endl
            << "  -i, --install <source> <file> [ <file> <number> ]"
            << std::endl
            << "  -r, --remove <source>" << std::endl
            << "  -l, --list" << std::endl
            << "      --help" << std::endl
            << "      --version";
        return (out);
    }

    const w32::string path =
        L"SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application";

    void Install ( int argc, wchar_t ** argv )
    {
        if ((argc != 2) && (argc != 4)) {
            throw WrongArgumentCount();
        }
        w32::rgs::Key sources(w32::rgs::Key::machine(),path);
        w32::rgs::Key log(sources,argv[0]);
        w32::rgs::Value types(log,L"TypesSupported");
        w32::rgs::Value file(log,L"EventMessageFile");
        w32::rgs::Value categories(log,L"CategoryMessageFile");
        w32::rgs::Value categorycount(log,L"CategoryCount");
        if ( argc == 3 )
        {
            int count = 0;
            std::wistringstream parser(argv[3]);
            if ( !(parser >> count) ) {
                throw NotANumber();
            }
            categorycount = count;
            categories = argv[2];
        }
        file = argv[1];
        types = w32::dbg::Event::Type::all();
    }

    void List ( int argc, wchar_t ** )
    {
        if ( argc != 0 ) {
            throw WrongArgumentCount();
        }
        w32::rgs::Key sources(w32::rgs::Key::machine(),path);
        w32::rgs::Keys subkeys(sources);
        do {
            std::cout << subkeys.result() << std::endl;
        } while ( subkeys.next() );
    }

    void Remove ( int argc, wchar_t ** argv )
    {
        if ( argc != 1 ) {
            throw WrongArgumentCount();
        }
        w32::rgs::Key sources(w32::rgs::Key::machine(),path);
        sources.delete_(argv[0]);
    }

    void Version ( int argc, wchar_t ** )
    {
        if ( argc != 0 ) {
            std::cerr << "Warning: ignoring unexpected arguments." << std::endl;
        }
        std::cout << version << std::endl;
    }

    void Help ( int argc, wchar_t ** )
    {
        if ( argc != 0 ) {
            std::cerr << "Warning: ignoring unexpected arguments." << std::endl;
        }
        std::cout << usage << std::endl;
    }

    // Map option names to jobs.
    typedef void(*Action)(int,wchar_t**);
    struct Option {
        const wchar_t * id;
        const wchar_t * name;
        Action action;
    };
    static const Option options[] = {
        { L"-i", L"--install", &Install },
        { L"-l", L"--list",    &List },
        { L"-r", L"--remove",  &Remove },
        { L"",   L"--version", &Version },
        { L"",   L"--help",    &Help },
    };
    static const int optioncount = sizeof(options) / sizeof(Option);

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // At least one effective argument is required.
        if ( argc < 2 ) {
            std::cerr << "Nothing to do. Use '--help' for usage." << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Find the appropriate action to excute.
        const w32::string option = argv[1];
        Action action = 0;
        for ( int i = 0; ((i < optioncount) && (action == 0)); ++i )
        {
            if ((option == options[i].id) || (option == options[i].name)) {
                action = options[i].action;
            }
        }
        
            // Make sure we found something.
        if ( action == 0 ) {
            throw InvalidOption();
            return (EXIT_FAILURE);
        }
        
            // Execute it.
        (*action)(argc-2,argv+2);
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.rgs.lib" )
