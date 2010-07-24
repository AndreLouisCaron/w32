// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Principal.hpp>
#include <w32/ts-2/Definition.hpp>

namespace {

    ::IPrincipal * fetch ( ::ITaskDefinition * task )
    {
        ::IPrincipal * principal = 0;
        const w32::com::Result result = task->get_Principal(&principal);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskDefinition, get_Principal, result);
        }
        return (principal);
    }

}

namespace w32 { namespace ts {

    Principal::Principal ( Definition& task )
        : com::Wrapper< ::IPrincipal >( ::fetch(task.ptr().value()) )
    {
    }

} }
