// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
