#ifndef _w32_tp_Cleanup_hpp__
#define _w32_tp_Cleanup_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 { namespace tp {

    class Cleanup
    {
        /* nested types. */
    public:
        typedef Reference< ::PTP_CLEANUP_GROUP > Handle;

        /* class methods. */
    public:
        const Handle claim ( ::PTP_CLEANUP_GROUP object );
        const Handle proxy ( ::PTP_CLEANUP_GROUP object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Cleanup ();

        /* methods. */
    public:
        const Handle& handle () const;

        void close ( bool cancel, void * context = 0 );
    };

} }

#endif /* _w32_tp_Cleanup_hpp__ */
