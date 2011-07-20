#ifndef _w32_ipc_configure_hpp__
#define _w32_ipc_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

    // API headers.
#ifndef _PSAPI_H_
#   include <PSApi.h>
#endif
#ifndef _INC_TOOLHELP32
#   include <TlHelp32.h>
#endif

#endif /* _w32_ipc_configure_hpp__ */
