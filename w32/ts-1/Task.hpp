#ifndef _w32_ts_Task_hpp__
#define _w32_ts_Task_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Scheduler;

    class W32_TS_EXPORT Task :
        public com::Wrapper< ::ITask >
    {
        /* class methods. */
    public:
        static Task create ( Scheduler& scheduler, const string& name );

        /* construction. */
    private:
        Task ( const Ptr& task );

    public:
        Task ( Scheduler& scheduler, const string& name );

        /* methods. */
    public:
        string application () const;
        string creator () const;
        string account () const;
        word triggers () const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::ITask > ()
{
    return (IID_ITask);
}

#endif /* _windows_Task_hpp__ */
