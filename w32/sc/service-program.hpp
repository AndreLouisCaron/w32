#ifndef _w32_svc_service_program_hpp__
#define _w32_svc_service_program_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32/svc.hpp>

namespace {

    extern const char ServiceName[];
    extern const char LogName[];

    w32::dword run
        ( w32::svc::Service::StatusHandler& status, w32::dbg::EventLog& log );

}


#endif /* _w32_svc_service_program_hpp__ */
