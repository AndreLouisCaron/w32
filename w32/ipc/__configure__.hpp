#ifndef _w32_ipc_configure_hpp__
#define _w32_ipc_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#ifdef __building_w32_ipc__
#   define W32_IPC_EXPORT __declspec(dllexport)
#   ifdef _MSC_VER
#       pragma warning ( push )
#       pragma warning ( disable : 4250 ) // Mixins.
#       pragma warning ( disable : 4251 ) // DLL-exported templates.
#       pragma comment ( lib, "PSApi.lib" )
#   endif
#else
#   define W32_ICP_EXPORT __declspec(dllimport)
#endif

    // API headers.
#ifndef _PSAPI_H_
#   include <PSApi.h>
#endif

#endif /* _w32_ipc_configure_hpp__ */
