// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-2/Definition.hpp>
#include <w32.ts-2/Service.hpp>

namespace {

    ::ITaskDefinition * allocate ( ::ITaskService * service )
    {
        ::ITaskDefinition * task = 0;
        const ::DWORD flags = 0;
        const w32::com::Result result = service->NewTask(flags, &task);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService, NewTask, result);
        }
        return (task);
    }

}

namespace w32 { namespace ts {

    Definition::Definition ( Service& service )
        : com::Wrapper< ::ITaskDefinition >( ::allocate(service.ptr().value()) )
    {
    }

} }
