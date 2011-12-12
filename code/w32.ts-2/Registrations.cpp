// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-2/Registrations.hpp>
#include <w32.ts-2/Folder.hpp>

namespace {

    ::IRegisteredTaskCollection * fetch ( ::ITaskFolder * parent )
    {
        ::IRegisteredTaskCollection * tasks = 0;
        const ::LONG flags = 0;
        const w32::com::Result result = parent->GetTasks(flags, &tasks);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskFolder, GetTasks, result);
        }
        return (tasks);
    }

}

namespace w32 { namespace ts {

    Registrations::Registrations ( const Folder& folder )
        : com::Wrapper< ::IRegisteredTaskCollection >
              ( ::fetch(folder.ptr().value()) )
    {
    }

    long Registrations::count () const
    {
        long value = 0;
        const com::Result result = ptr()->get_Count(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTaskCollection, get_Count, result);
        }
        return (value);
    }

} }
