#ifndef _w32_net_hpp__
#define _w32_net_hpp__

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

#include "__configure__.hpp"

namespace w32 {
    namespace net {}
}

/*!
 * @defgroup w32-net Networking services.
 */

#include <w32.net/Buffer.hpp>
#include <w32.net/Context.hpp>
#include <w32.net/Event.hpp>
#include <w32.net/Host.hpp>
#include <w32.net/integers.hpp>
#include <w32.net/select.hpp>
#include <w32.net/Set.hpp>
#include <w32.net/StreamSocket.hpp>
#include <w32.net/sockstream.hpp>
#include <w32.net/Timespan.hpp>
#include <w32.net.ipv4/Address.hpp>
#include <w32.net.ipv4/EndPoint.hpp>
#include <w32.net.ipv6/Address.hpp>
#include <w32.net.tcp/Connection.hpp>
#include <w32.net.tcp/Connections.hpp>
#include <w32.net.tcp/Listener.hpp>
#include <w32.net.tcp/State.hpp>
#include <w32.net.tcp/Stream.hpp>
#include <w32.net.udp/Socket.hpp>

#endif /* _w32_net_hpp__ */
