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

#include <w32.ts-2/Handler.hpp>

namespace w32 { namespace ts {

    void Handler::Status::completed ( com::Result status )
    {
        const com::Result result = ptr()->TaskCompleted(status.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskHandlerStatus, TaskCompleted, result);
        }
    }

    void Handler::Status::status
        ( short percentage, const bstring& message )
    {
        const com::Result result =
            ptr()->UpdateStatus(percentage, message.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskHandlerStatus, UpdateStatus, result);
        }
    }

    ::HRESULT __stdcall Handler::Start ( ::IUnknown * scheduler, ::BSTR data )
    try
    {
        Status status(com::cast< ::ITaskHandlerStatus >(scheduler));
        start(status,bstring(data));
        return (S_OK);
    }
    catch ( const com::Error& ) {
        return (E_FAIL);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

    ::HRESULT __stdcall Handler::Stop ( ::HRESULT * result )
    {
        *result = S_OK;
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Handler::Pause ()
    {
        return (E_NOTIMPL);
    }

    ::HRESULT __stdcall Handler::Resume ()
    {
        return (E_NOTIMPL);
    }

} }
