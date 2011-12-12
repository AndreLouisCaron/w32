#ifndef _w32_shl_taskbar_application_hpp__
#define _w32_shl_taskbar_application_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.gdi.hpp>
#include <w32.shl.hpp>
#include <utility>

namespace {

    typedef void(*Callback)();
    typedef std::pair< w32::string, Callback > Entry;

}

#endif /* _w32_shl_taskbar_application_hpp__ */
