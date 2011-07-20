// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Handler.hpp>

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
