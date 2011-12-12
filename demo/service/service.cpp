// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.dbg.hpp>
#include <w32.mt.hpp>

#include <w32/app/service-program.hpp>

namespace {

    class Service
    {
        /* nested types. */
    private:
        typedef w32::sc::Service::Handler Handler;
        typedef w32::sc::Service::Status Status;

        /* class data. */
    public:
        static const wchar_t * name () {
            return (L"w32++ test-service");
        }

        /* data. */
    private:
        Handler& myHandler;
        w32::dbg::Log myLog;

        /* construction. */
    public:
        Service ( w32::sc::Service::Handler& handler, int, wchar_t** )
            : myHandler(handler), myLog(name())
        {
        }

        ~Service ()
        {
        }

        /* operators. */
    public:
        void operator() ()
        {
            while ( myHandler.current() == Status::running )
            {
                w32::mt::sleep(w32::Timespan(1000));
            }
        }
    };

}

#include <w32/app/service-program.cpp>

#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.rgs.lib" )
#pragma comment ( lib, "w32.mt.lib" )
#pragma comment ( lib, "w32.sc.lib" )
