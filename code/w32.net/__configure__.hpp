#ifndef _w32_net_configure_hpp__
#define _w32_net_configure_hpp__

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

// Exceptionally, include <../w32/__configure__.hpp> *after* <WinSock2.h>.

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
#include "../w32/__configure__.hpp"

    // Extra headers, to use on demand.
#if 1
#   include <Ws2TcpIp.h> // Advanced tcp/ip networking.
#endif
#if 0
#   include <Ws2Bth.h>   // Bluetooth networking.
#   include <AF_irda.h>  // Infra-red data acquisition.
#endif

#endif /* _w32_net_configure_hpp__ */
