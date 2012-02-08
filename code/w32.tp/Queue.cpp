// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.tp/Queue.hpp>
#include <w32.tp/Cleanup.hpp>
#include <w32.tp/Pool.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace tp {

    Queue::Queue ( Pool& pool )
    {
        ::InitializeThreadpoolEnvironment(&myData);
        ::SetThreadpoolCallbackPool(&myData, pool.handle());
    }

    Queue::~Queue ()
    {
        ::DestroyThreadpoolEnvironment(&myData);
    }

    Queue::Data& Queue::data ()
    {
        return (myData);
    }

    const Queue::Data& Queue::data () const
    {
        return (myData);
    }

    void Queue::cleanup ( Cleanup& cleanup, Cancel cancel )
    {
        ::SetThreadpoolCallbackCleanupGroup
            (&myData, cleanup.handle(), cancel);
    }

} }
