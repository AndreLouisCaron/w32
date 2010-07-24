// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.rgs.hpp>
#include <algorithm>
#include <sstream>

namespace {

    w32::string keypath ( const wchar_t * x )
    {
        w32::string path(x);
        std::replace(path.begin(), path.end(), L'/', L'\\');
        return (path);
    }

    struct WrongArgumentCount : public std::exception {
        virtual const char * what () const throw() {
            return ("missing argument(s)");
        }
    };

    struct InvalidHiveName : public std::exception {
        virtual const char * what () const throw() {
            return ("invalid registry hive name");
        }
    };

    struct InvalidTypeName : public std::exception {
        virtual const char * what () const throw() {
            return ("invalid registry value type name");
        }
    };

    struct InvalidValueFormat : public std::exception {
        virtual const char * what () const throw() {
            return ("value format does not match type");
        }
    };

    std::ostream& program ( std::ostream& out ) {
        return (out << "registry");
    }

    std::ostream& author ( std::ostream& out ) {
        return (out << "Andre Louis Caron");
    }

    std::ostream& copyright_holder ( std::ostream& out ) {
        return (out << author);
    }

    std::ostream& copyright_dates ( std::ostream& out ) {
        return (out << "2008");
    }

    std::ostream& copyright ( std::ostream& out )
    {
        out << "Copyright (c) " << copyright_holder
            << ' ' << copyright_dates << '.';
        return (out);
    }

    std::ostream& stamp ( std::ostream& out ) {
        return (out << __DATE__ << ' ' << __TIME__);
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

    std::ostream& invalid ( std::ostream& out ) {
        return (out << "Error: invalid purpose -> ");
    }

    std::ostream& usage ( std::ostream& out )
    {
        out << "  Usage: registry <action> [ arguments... ]"
            << std::endl
            << "    Performs an action on a registry key or value." << std::endl
            << std::endl
            << "  <action> is one of:" << std::endl
            << "    -c, --create-key   <hive> <path> <name>" << std::endl
            << "    -d, --delete-key   <hive> <path>" << std::endl
            << "    -k, --list-keys    <hive> <path>" << std::endl
            << "    -v, --list-values  <hive> <path>" << std::endl
            << "    -g, --get-value    <hive> <path> <name>" << std::endl
            << "    -s, --set-value    <hive> <path> <name> <type> <data>"
            << "    -r, --remove-value <hive> <path> <name>" << std::endl
            << std::endl
            << "        --help" << std::endl
            << "        --version" << std::endl
            << std::endl
            << "  <path> accepts both '/' and '\\' as separators." << std::endl
            << std::endl
            << "  <hive> is one of:" << std::endl
            << "    user          HKEY_CURRENT_USER" << std::endl
            << "    users         HKEY_USERS" << std::endl
            << "    machine       HKEY_LOCAL_MACHINE" << std::endl
            << "    classes       HKEY_CLASSES_ROOT" << std::endl
            << "    configuration HKEY_CURRENT_CONFIG (Windows Vista+)" << std::endl
            << std::endl
            << "  <type> is one of:" << std::endl
            << "    dword         (REG_DWORD: non-negative integer)" << std::endl
            << "    string        (REG_SZ   : character string    )" << std::endl;
        return (out);
    }

    w32::rgs::Key ParseHive ( const w32::string& name )
    {
        struct Association {
            const char * name;
            w32::rgs::Key hive;
        };
        static const Association values[] = {
            { "machine", w32::rgs::Key::machine() },
            { "classes", w32::rgs::Key::classes() },
            { "user", w32::rgs::Key::user() },
            { "users", w32::rgs::Key::users() },
#       if (_WIN32_WINNT  >= 0x0600)
            { "configuration", w32::rgs::Key::configuration() },
#       endif
        };
        static const int valuecount = sizeof(values) / sizeof(Association);
        for ( int i = 0; i < valuecount; ++i ) {
            if ( name == values[i].name ) {
                return values[i].hive;
            }
        }
        throw InvalidHiveName();
    }

    w32::rgs::Type ParseType ( const w32::string& name )
    {
        struct Association {
            const char * name;
            w32::rgs::Type type;
        };
        static const Association values[] = {
            { "string", w32::rgs::Type::string() },
            { "dword", w32::rgs::Type::dword() },
        };
        static const int valuecount = sizeof(values) / sizeof(Association);
        for ( int i = 0; i < valuecount; ++i ) {
            if ( name == values[i].name ) {
                return values[i].type;
            }
        }
        throw InvalidTypeName();
    }

    void EnumerateSubKeys (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 1 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        
        const w32::rgs::Key key(hive, path);
        for ( w32::rgs::Keys search(key); search.next(); ) {
            std::wcout << search.result() << std::endl;
        }
    }

    void EnumerateValues (
        w32::rgs::Key hive, int argc, wchar_t ** argv
    )
    {
        if ( argc != 1 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        const w32::rgs::Key key(hive,path);
        for ( w32::rgs::Values search(key); search.next(); )
        {
            const w32::string name(search.result());
            const w32::rgs::Value value(key,name);
            const w32::rgs::Type type = value.type();
            if ( type == w32::rgs::Type::string() ) {
                std::cout << "string:";
            }
            else if ( type == w32::rgs::Type::dword() ) {
                std::cout << "dword:";
            }
            else {
                std::cout << "unsupported:";
            }
            std::wcout << name << std::endl;
        }
    }

    void QueryValue (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 2 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        const w32::string name(argv[1]);
        const w32::rgs::Key key(hive,path);
        const w32::rgs::Value value(key,name);
        std::wcout << w32::string(value) << std::endl;
    }

    void SetValue (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 4 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        const w32::string name(argv[1]);
        const w32::rgs::Type type(ParseType(argv[2]));
        const w32::string data(argv[3]);
        
        w32::rgs::Key key(hive,path);
        w32::rgs::Value value(key,name);
        if ( type == w32::rgs::Type::string() ) {
            value = data;
        }
        else if ( type == w32::rgs::Type::dword() )
        {
            std::wistringstream parser(data);
            ::DWORD number = 0;
            if ( !(parser >> number) ) {
                throw InvalidValueFormat();
            }
            value = number;
        }
    }

    void CreateKey (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 2 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        const w32::string name(argv[1]);
        w32::rgs::Key parent(hive,path);
        w32::rgs::Key::create(parent,name);
    }

    void RemoveValue (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 2 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        const w32::string name(argv[1]);
        w32::rgs::Key key(hive,path);
        key.remove(name);
    }

    void DeleteKey (
        w32::rgs::Key hive, int argc, wchar_t ** argv
        )
    {
        if ( argc != 1 ) {
            throw WrongArgumentCount();
        }
        const w32::string path = keypath(argv[0]);
        hive.delete_(path);
    }

        // Map option names to jobs.
    typedef void(*Action)(const w32::rgs::Key,int,wchar_t**);
    struct Option {
        const char * id;
        const char * name;
        Action action;
    };
    static const Option options[] = {
        { "-c", "--create-key", &CreateKey },
        { "-d", "--delete-key", &DeleteKey },
        { "-k", "--list-keys", &EnumerateSubKeys },
        { "-v", "--list-values", &EnumerateValues },
        { "-g", "--get-value", &QueryValue },
        { "-s", "--set-value", &SetValue },
        { "-r", "--remove-value", &RemoveValue },
    };
    static const int optioncount = sizeof(options) / sizeof(Option);

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // At least one effective argument is required.
        if ( argc < 2 ) {
            std::cerr << "  Nothing to do. Use '--help' for usage." << std::endl;
            return (EXIT_FAILURE);
        }
        const w32::string purpose(argv[1]);
        
            // Treat special options first.
        if ( purpose == "--help" )
        {
            std::cerr << usage << std::endl;
            return (EXIT_FAILURE);
        }
        if ( purpose == "--version" )
        {
            std::cerr << version << std::endl;
            return (EXIT_FAILURE);
        }
        
        if ( argc < 3 ) {
            throw WrongArgumentCount();
        }
        
        const w32::string option = argv[1];
        const w32::rgs::Key hive = ParseHive(argv[2]);
        
            // Find the appropriate action to excute.
        Action action = 0;
        for ( int i = 0; ((i < optioncount) && (action == 0)); ++i )
        {
            if ((option == options[i].id) || (option == options[i].name)) {
                action = options[i].action;
            }
        }
        
            // Make sure we found something.
        if ( action == 0 ) {
            std::cerr << invalid << purpose << '.' << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Execute it.
        (*action)(hive,argc-3,argv+3);
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.rgs.lib" )
