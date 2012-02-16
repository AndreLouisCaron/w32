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

#include <w32.gdi/MappingMode.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace gdi {

    const MappingMode MappingMode::text ()
    {
        return (MM_TEXT);
    }

    MappingMode::Selection::Selection (
        const DeviceContext& device, const MappingMode& mode
        )
        : myDevice(device.handle()),
              myPredecessor(::SetMapMode(myDevice, mode.value()))
    {
        if ( myPredecessor == 0 ) {
            UNCHECKED_WIN32C_ERROR(SetMapMode,::GetLastError());
        }
    }

    MappingMode::Selection::~Selection ()
    {
        ::SetMapMode(myDevice,myPredecessor);
    }

    MappingMode MappingMode::of ( const DeviceContext& device )
    {
        const int mode = ::GetMapMode(device.handle());
        if ( mode == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetMapMode, error);
        }
        return (MappingMode(mode));
    }

    MappingMode::MappingMode ( Value value )
        : myValue(value)
    {
    }

    MappingMode::Value MappingMode::value () const
    {
        return (myValue);
    }

} }
