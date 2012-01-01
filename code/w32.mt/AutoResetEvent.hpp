#ifndef _w32_mt_AutoResetEvent_hpp__
#define _w32_mt_AutoResetEvent_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Signal that some condition has been satisfied.
     *
     * The signal stays signaled until some wait on the object has been
     * satisfied.  The behavior is similar to a mutex except that lock is
     * "acquired" by one thread and "released" by another.
     *
     * @see ConditionVariable
     * @see ManualResetEvent
     */
    class AutoResetEvent :
        public Object
    {
        /* class methods. */
    public:
        static AutoResetEvent open ( const string& name );

        /* construction. */
    protected:
        explicit AutoResetEvent ( const Handle& handle );

    public:
        AutoResetEvent ();
        AutoResetEvent ( const string& name );

        /* methods. */
    public:
        void set ();

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_AutoResetEvent_hpp__ */
