#ifndef _w32_configure_hpp__
#define _w32_configure_hpp__

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

// Require that the build system provide a target Windows version.
#ifndef _WIN32_WINNT
#   error "Can't detect target Windows version."
#endif

// Older SDK headers can't see in the future.  Define Windows version macros if
// they're not provided by the SDK headers or the compiler.

#ifndef _WIN32_WINNT_WIN7
#   define _WIN32_WINNT_WIN7 0x0601
#endif

#ifndef _WIN32_WINNT_WS08
#   define _WIN32_WINNT_WS08 0x0600
#endif

#ifndef _WIN32_WINNT_VISTA
#   define _WIN32_WINNT_VISTA 0x0600
#endif

#ifndef _WIN32_WINNT_WS03
#   define _WIN32_WINNT_WS03 0x0502
#endif

#ifndef _WIN32_WINNT_WINXP
#   define _WIN32_WINNT_WINXP 0x0501
#endif

    // API headers.
#ifndef _WINSOCK2API_
#   include <WinSock2.h>
#endif
#ifndef _WINDOWS_
#   include <Windows.h>
#endif
#ifndef __oleidl_h__
#   include <OLEIdl.h>
#endif
    // Structured exception handling.
#ifndef _INC_EH
#   include <eh.h>
#endif

    // Remove conflicting macros.
#if (defined(big))
#   undef big
#endif
#if (defined(small))
#   undef small
#endif
#if (defined(min))
#   undef min
#endif
#if (defined(max))
#   undef max
#endif

#endif /* _w32_configure_hpp__ */
