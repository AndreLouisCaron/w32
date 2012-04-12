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

#include "TaskCreator.hpp"
#include "TaskDetailPrinter.hpp"
#include "TaskNamePrinter.hpp"
#include "TaskRemover.hpp"
#include "TriggerCreator.hpp"
#include <iostream>

namespace {

    w32::string widen ( const std::string& value ) {
        return w32::string(value.data());
    }

}

namespace {

        /*!
         * @brief Print the program header, including the copyright.
         */
    std::ostream & copyright ( std::ostream & out ) {
        out << "Task Scheduler, Copyright(c) Andre Louis Caron, 2008";
        return (out);
    }

        /*!
         * @brief Print the program's version.
         */
    std::ostream & version ( std::ostream & out ) {
        out << "Version 1.0.0, build 0";
        return (out);
    }

        /*!
         * @brief Print how to get help about using the program.
         */
    std::ostream & nothing ( std::ostream & out ) {
        out << "What is it you wish to do? See \'--help\' option.";
        return (out);
    }

        /*!
         * @brief Print how to get help about using the program.
         */
    std::ostream & invalid ( std::ostream & out ) {
        out << "Invalid argument, see \'--help\' option.";
        return (out);
    }

        /*!
         * @brief Print help with using the program.
         */
    std::ostream & usage ( std::ostream & out )
    {
        out << "Usage: task-scheduler <command> [ arguments... ]"
            << std::endl
            << "Command-line interface to the Microsoft Windows task scheduler."
            << std::endl
            << "  -l, --list         " << std::endl
            << "    Lists all registered tasks' names." << std::endl
            << "  -ld, --list-details" << std::endl
            << "    Lists all registered tasks' details." << std::endl
            << "  -d, --details       <task>" << std::endl
            << "    Lists details for a given task." << std::endl
            << "  -r, --remove        <task>" << std::endl
            << "  -n, --new           <name> [ properties... ]" << std::endl
            << "    Registers a new task." << std::endl
            << "  -t, --trigger       <task> [ properties... ]" << std::endl
            << "    Creates a new trigger for an existing task." << std::endl
            << "      --help" << std::endl
            << "      --version";
        return (out);
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    try
    {
        if ( argc < 2 ) {
            std::cout << nothing << std::endl;
            return (EXIT_FAILURE);
        }
        
        const w32::string option(argv[1]);
        if ((argc == 2) && (option == w32::string(L"--help"))) {
            std::cout << usage << std::endl;
            return (EXIT_FAILURE);
        }
        if ((argc == 2) && (option == w32::string(L"--version"))) {
            std::cout << version << std::endl;
            return (EXIT_FAILURE);
        }
        
        if ((argc == 2) && (option == w32::string(L"-l")))
        {
                // Print names of all registered tasks.
            TaskNamePrinter names;
            names();
        }
        else if ((argc == 2) && (option == w32::string(L"-ld")))
        {
                // Print details for all registered tasks.
            TaskDetailPrinter details;
            details();
        }
        else if ((argc > 2) && (option == w32::string(L"-r")))
        {
            TaskRemover remove;
                // Remove all listed tasks.
            wchar_t ** current   = argv + 2;
            wchar_t ** const end = current + (argc - 2);
            for ( ; current != end; ++current ) {
                try {
                    remove(*current);
                }
                catch ( const w32::com::Error& error ) {
                    std::wcerr
                        << L"Error removing task \'" << *current << L"\':"
                        << error.what() << std::endl;
                }
            }
        }
        else if ((argc > 2) && (option == w32::string(L"-d")))
        {
            TaskDetailPrinter details;
                // Print details for all listed tasks.
            wchar_t ** current   = argv + 2;
            wchar_t ** const end = current + (argc - 2);
            for ( ; current != end; ++current ) {
                try {
                    details(*current);
                }
                catch ( const w32::com::Error& error ) {
                    std::wcerr
                        << L"Error processing task \'" << *current << L"\':"
                        << error.what() << std::endl;
                }
            }
        }
        else if ((argc > 2) && (option == w32::string(L"-n")))
        {
            TaskCreator create(argv[2]);
                // Parse and set properties.
            wchar_t ** current   = argv + 3;
            wchar_t ** const end = current + (argc - 3);
            for ( ; current != end; ++current ) {
                create(*current);
            }
                // Save the task.
            create();
        }
        else if ((argc > 2) && (option == w32::string(L"-t")))
        {
            TriggerCreator trigger(argv[2]);
                // Parse and set properties.
            wchar_t ** current   = argv + 3;
            wchar_t ** const end = current + (argc - 3);
            for ( ; current != end; ++current ) {
                trigger(*current);
            }
                // Save the task.
            trigger();
        }
        else {
            std::cerr << invalid << std::endl;
            return (EXIT_FAILURE);
        }
        
        return (EXIT_SUCCESS);
    }
    catch ( const w32::com::Error& error ) {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/app/console-program.cpp>
