#ifndef _w32_net_configure_hpp__
#define _w32_net_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

// Exceptionally, include <../__configure__.hpp> *after* <WinSock2.h>.

#ifdef __building_w32_net__
#   define W32_NET_EXPORT __declspec(dllexport)
#   include "../__compiler-intro__.hpp"
#   ifdef _MSC_VER
#       pragma comment ( lib, "WS2_32.lib" )
#   endif
#else
#   define W32_NET_EXPORT __declspec(dllimport)
#endif

#ifndef _WINSOCK2API_
#   if (defined(_INC_WINDOWS))
#       error "You shouldn't include <Windows.h> before this header."
#   endif
#   if (defined(_WINSOCKAPI_))
#       error "You shouldn't include <WinSock.h> (version 1) before this header."
#   endif
#   include <WinSock2.h>
#endif

    // Exceptionally, include this *after* <WinSock2.h>.
#include "../__configure__.hpp"

    // Extra headers, to use on demand.
#if 1
#   include <Ws2TcpIp.h> // Advanced tcp/ip networking.
#endif
#if 0
#   include <Ws2Bth.h>   // Bluetooth networking.
#   include <AF_irda.h>  // Infra-red data acquisition.
#endif

#endif /* _w32_net_configure_hpp__ */
