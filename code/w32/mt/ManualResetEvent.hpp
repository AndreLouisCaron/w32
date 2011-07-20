#ifndef _w32_mt_ManualResetEvent_hpp__
#define _w32_mt_ManualResetEvent_hpp__

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

    class ManualResetEvent :
        public Object
    {
        /* class methods. */
    public:
        static ManualResetEvent open ( const string& name );

        /* construction. */
    protected:
        explicit ManualResetEvent ( const Handle& handle );

    public:
        ManualResetEvent ();
        explicit ManualResetEvent ( const string& name );

        /* methods. */
    public:
        void set ();
        void reset ();

        void wait () const;
        bool wait ( const Timespan& timeout ) const;
        bool test () const;

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_ManualResetEvent_hpp__ */
