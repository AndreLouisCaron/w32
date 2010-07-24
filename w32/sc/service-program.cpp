// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32/dbg.hpp>
#include <w32/svc.hpp>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>

// Must define: ServiceName and LogName strings, a "run()" function as well as
// DebugMessage and UncaughtException classes, inheriting from w32::dbg::Event.

namespace {

    std::ostream& usage ( std::ostream& out )
    {
        out << "Usage :"
            << std::endl
            << "    service.exe /i"
            << std::endl
            << "      install the service. The service control manager will "
            << "expect to find the executable in it's current location. If "
            << "you wish to move it, you will need to re-install it."
            << std::endl << std::endl
            << "    service.exe /u"
            << "      uninstall the service."
            << std::endl << std::endl
            << "    service.exe /?"
            << std::endl
            << "      print help about using this program (you're reading it)"
            << std::endl;
        return (out);
    }

    std::ostream& version ( std::ostream& out )
    {
        return (out);
    }

    /*!
     * @brief Callback for the system to launch the service program.
     */
    void __stdcall ServiceMain ( w32::dword argc, wchar_t ** argv );

    int Install ( int argc, wchar_t ** argv )
    {
        // Fetch the full path to the executable.
        const w32::string executable = w32::CurrentModule().path();

        // Could we register the event source at the same time?
        w32::svc::Database scm;
        w32::svc::NewService service(scm,::ServiceName,executable);

        return (EXIT_SUCCESS);
    }

    int Execute ( int argc, wchar_t ** argv )
    {
        w32::svc::Database scm;
        scm.run(::ServiceName,&ServiceMain);
        return (EXIT_SUCCESS);
    }

    int Remove ( int argc, wchar_t ** argv )
    {
        w32::svc::Database scm;
        w32::svc::ExistingService service(scm,::ServiceName);
        service.remove();
        return (EXIT_SUCCESS);
    }

    int Version ( int, wchar_t ** )
    {
        std::cout << version << std::endl;
        return (EXIT_SUCCESS);
    }

    int Help ( int, wchar_t ** )
    {
        std::cout << usage << std::endl;
        return (EXIT_FAILURE);
    }

    // Map option names to jobs.
    typedef int(*Action)(int argc,wchar_t** argv);
    struct Option {
        const wchar_t * id;
        const wchar_t * name;
        Action action;
    };
    static const Option options[] = {
        { L"-i", L"--install", &Install },
        { L"-r", L"--remove" , &Remove  },
        { L""  , L"--version", &Version },
        { L""  , L"--help"   , &Help    },
    };
    static const int optioncount = sizeof(options) / sizeof(Option);

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        // If run with no arguments, start the service.
        if ( argc < 2 ) {
            return (Execute(argc-1,argv+1));
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

        // When no match occurs, execute the service.
        if ( action == 0 ) {
            return (Execute(argc-1,argv+1));
        }

        // Execute it.
        return ((*action)(argc-2,argv+2));

        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

namespace {

    void __stdcall ServiceMain ( w32::dword argc, wchar_t ** argv )
    {
        try
        {
            w32::dbg::StructuredException::FilterReplacement filter;

            // Get service status and report startup as soon as possible.
            w32::svc::Service::StatusHandler status(::ServiceName);

            // Open the event log for the service.
            w32::dbg::NamedEventLog log(::LogName);
            try {
                status.exit(run(status,log));
            }
            // Catch debugging exceptions.
            catch ( const w32::dbg::UncheckedError& error )
            {
                log.report(DebugMessage(error.what()));
                status.exit(EXIT_FAILURE);
            }
            catch ( const w32::dbg::StructuredException& error )
            {
                log.report(DebugMessage(error.what()));
                status.exit(EXIT_FAILURE);
            }
            catch ( const std::exception& error )
            {
                log.report(DebugMessage(error.what()));
                status.exit(EXIT_FAILURE);
            }
            // Catch anything else.
            catch ( ... )
            {
                log.report(UncaughtException());
                status.exit(EXIT_FAILURE);
            }
        }
        // Can't do anything at this point: the only way to signal stuff is
        // through the event log, and it either could not be opened or is
        // already closed.
        catch ( ... ) {
        }
    }

}
