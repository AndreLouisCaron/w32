#ifndef _w32_ts_Scheduler_hpp__
#define _w32_ts_Scheduler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

// Task scheduler code examples:
// see http://msdn2.microsoft.com/en-us/library/aa383579(VS.85).aspx

namespace w32 { namespace ts {

    class W32_TS_EXPORT Scheduler :
        public com::Wrapper< ::ITaskScheduler >
    {
        /* nested types. */
    public:
        class ConnectionFailure {};

        /* construction. */
    public:
        Scheduler ();

        /* methods. */
    public:
        void remove ( const string& task );
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof<::ITaskScheduler> ()
{
    return (IID_ITaskScheduler);
}

#endif /* _w32_ts_Scheduler_hpp__ */
