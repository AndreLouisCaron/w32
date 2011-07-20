// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/System.hpp>

namespace w32 {

    System::System ()
    {
        // Check out: GetNativeSystemInfo().
        ::GetSystemInfo(&myData);
    }

    System::Data& System::data ()
    {
        return (myData);
    }

    const System::Data& System::data () const
    {
        return (myData);
    }

    Architecture System::architecture () const
    {
        return (Architecture::of(*this));
    }

    dword System::pagesize () const
    {
        return (myData.dwPageSize);
    }

    dword System::processors () const
    {
        return (myData.dwNumberOfProcessors);
    }

    dword System::granularity () const
    {
        return (myData.dwAllocationGranularity);
    }

}
