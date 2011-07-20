// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ts-2/Actions.hpp>
#include <w32/ts-2/Definition.hpp>

namespace {

    ::IActionCollection * fetch ( ::ITaskDefinition * task )
    {
        ::IActionCollection * collection = 0;
        const w32::com::Result result = task->get_Actions(&collection);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskDefinition, get_Actions, result);
        }
        return (collection);
    }

}

namespace w32 { namespace ts {

    Actions::Actions ( Definition& task )
        : com::Wrapper< ::IActionCollection >(::fetch(task.ptr().value()))
    {
    }

} }
