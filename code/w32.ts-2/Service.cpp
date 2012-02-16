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

#include <w32.ts-2/Service.hpp>
#include <w32/Variant.hpp>

namespace {

    ::ITaskService * allocate ()
    {
        void * scheduler = 0;
        const w32::com::Result result = ::CoCreateInstance(
            CLSID_TaskScheduler, NULL, CLSCTX_INPROC_SERVER,
            IID_ITaskService, &scheduler
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService,CoCreateInstance,result);
        }
        return (static_cast<::ITaskService*>(scheduler));
    }

}

namespace w32 { namespace ts {

    Service::Service ()
        : com::Wrapper< ::ITaskService >( ::allocate() )
    {
        const Variant ignored;
        const Variant& domain = ignored;
        const Variant& computer = ignored;
        const Variant& account = ignored;
        const Variant& password = ignored;
        const com::Result result = ptr()->Connect(
            computer.value(), account.value(), domain.value(), password.value()
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService,Connect,result);
        }
    }

    bstring Service::domain () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_ConnectedDomain(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService,get_ConnectedDomain,result);
        }
        return (bstring(value));
    }

    bstring Service::server () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_TargetServer(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService,get_TargetServer,result);
        }
        return (bstring(value));
    }

    bstring Service::user () const
    {
        ::BSTR value = 0;
        const com::Result result = ptr()->get_ConnectedUser(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService,get_ConnectedUser,result);
        }
        return (bstring(value));
    }

} }
