#ifndef _w32_ts_Tasks_hpp__
#define _w32_ts_Tasks_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Scheduler;

        /*!
         * @brief Enumerate all scheduled task names.
         */
    class W32_TS_EXPORT Tasks :
        public com::Wrapper< ::IEnumWorkItems >
    {
        /* construction. */
    public:
        explicit Tasks ( const Scheduler& scheduler );

        /* methods. */
    public:
        bool next ( string& name );
    };

} }

#endif /* _w32_ts_Tasks_hpp__ */
