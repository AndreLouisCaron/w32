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

/*!
 * @file w32.net.irda/DeviceSearch.cpp
 * @author Andre Caron
 */

#include <w32.net.irda/DeviceSearch.hpp>
#include <w32/Error.hpp>

// http://msdn.microsoft.com/en-us/library/ms738544(VS.85).aspx

namespace {

    // Computs size (in bytes) of "extended" array.
    int size ( int count ) {
        return (sizeof(::DEVICELIST)+((count-1)*sizeof(::IRDA_DEVICE_INFO)));
    }

    // Allocate "extensible" array.
    ::DEVICELIST * allocate ( int size ) {
        return (static_cast<::DEVICELIST*>(operator new(size)));
    }

    // Fetch size of structure to allocate.
    int count ( ::SOCKET engine )
    {
        int count = 0;
        const int result = ::getsockopt(
                               engine, SOL_IRLMP, IRLMP_ENUMDEVICES, 0, &count
                           );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(getsockopt,::WSAGetLastError());
        }
        return (count);
    }

    const ::DEVICELIST * search ()
    {
        const ::SOCKET engine = ::socket(AF_IRDA, SOCK_STREAM, 0);
        if ( engine == INVALID_SOCKET )
        {
            const int error = ::WSAGetLastError();
            // May return WSAENETDOWN to indicate no IrDA support.
            UNCHECKED_WIN32C_ERROR(socket, error);
        }

        // Get a list of proper size.
        int length = size(count(engine));
        ::DEVICELIST *const list = allocate(length);

        const int result = ::getsockopt(
                               engine, SOL_IRLMP, IRLMP_ENUMDEVICES, (char*)list, &length
                           );
        if ( result == SOCKET_ERROR ) {
            UNCHECKED_WIN32C_ERROR(getsockopt,::WSAGetLastError());
        }

        return (list);
    }

}

namespace w32 {
    namespace net {
        namespace irda {

            DeviceSearch::DeviceSearch ()
                : myDevices(search())
            {
            }

            DeviceSearch::~DeviceSearch ()
            {
                operator delete(myDevices);
            }

        }
    }
}
