// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ts-1/Tasks.hpp>
#include <w32.ts-1/Scheduler.hpp>
#include <w32/Reference.hpp>

namespace {

    void release ( wchar_t * object )
    {
        ::CoTaskMemFree(object);
    }

    typedef w32::Reference< wchar_t* > Buffer;

    Buffer claim ( wchar_t * object )
    {
        return (Buffer(object, &release));
    }

    ::IEnumWorkItems * create ( ::ITaskScheduler * scheduler )
    {
        ::IEnumWorkItems * enumeration = 0;
        const w32::com::Result result = scheduler->Enum(&enumeration);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler, Enum, result);
        }
        return (enumeration);
    }

}

namespace w32 { namespace ts {

    Tasks::Tasks ( const Scheduler& scheduler )
        : com::Wrapper< ::IEnumWorkItems >( ::create(scheduler.ptr().value()) )
    {
    }

    bool Tasks::next ( string& name )
    {
        ::LPWSTR * names = 0;
        ::DWORD count = 0;
        const com::Result result = ptr()->Next(1, &names, &count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumWorkItems,Next,result);
        }
        if ( count == 0 ) {
            return (false);
        }
        name = ::claim(names[0]);
        return (true);
    }

} }
