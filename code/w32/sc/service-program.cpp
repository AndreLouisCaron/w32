// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/sc/service-program.hpp>

namespace {

    void __stdcall run ( w32::dword argc, wchar_t** argv )
    {
        typedef w32::sc::Service::Status Status;
        
          // access registered service.
        w32::sc::Service::Handler handler(Service::name());
        
          // perform critical initialization (e.g. without these
          // steps, the service should simply not be able to run).
        { Service service(handler, argc, argv);
            
              // let the service control manager know we've started.
            handler.signal(Status::running);
            
            try {
                  // launch main service function.
                service();
                
                  // let the service control manager know we've succeeded.
                handler.exit(EXIT_SUCCESS);
            }
            catch ( ... )
            {
                  // let the service control manager know we've failed.
                handler.exit(EXIT_FAILURE);
            }
            
              // let the service control manager know we're cleaning up.
            handler.signal(Status::stopping);
            
              // perform critical clean-up (e.g. if it doesn't
              //  complete, the service should be considered failed).
            // ...
        }
        
          // let the service control manager know we've stopped.
        handler.signal(Status::stopped);
    }

    void start ( w32::sc::Database& database, int, wchar_t ** )
    {
          // access registered service.
        database.run(Service::name(), &run);
    }

    void create ( w32::sc::Database& database, int, wchar_t ** )
    {
          // register new service.
        w32::sc::Service service
            (database, Service::name(), w32::Module().path());
    }

    void remove ( w32::sc::Database& database, int, wchar_t ** )
    {
          // access registered service.
        w32::sc::Service service(database, Service::name());
          // initiate removal procedure.
        service.remove();
    }

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        w32::sc::Database database;
        if ( argc > 1 )
        {
            const w32::string command(argv[1]);
            if ( command == L"create" ) {
                create(database, argc-1, argv+1);
            }
            else if ( command == L"remove" ) {
                remove(database, argc-1, argv+1);
            }
            else {
                std::wcout
                    << L"Unknown command '" << command << L"'."
                    << std::endl;
                return (EXIT_FAILURE);
            }
        }
        else {
            start(database, argc-1, argv+1);
        }
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>
