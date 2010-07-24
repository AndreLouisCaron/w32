#ifndef _w32_ts2_Registration_hpp__
#define _w32_ts2_Registration_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Definition;
    class Folder;
    class State;
    class Registrations;

    class W32_TS2_EXPORT Registration :
        public com::Wrapper< ::IRegisteredTask >
    {
        /* construction. */
    public:
        explicit Registration ( Folder& folder, Definition& task );
        explicit Registration ( Registrations& folder, long task );

        /* methods. */
    public:
        bstring name () const;
        bstring path () const;
        bstring xml () const;
        State state () const;
        bool enabled () const;
        void enabled ( bool activate );
        void enable ();
        void disable ();
        void stop ();
    };

} }

#endif /* _w32_ts2_Registration_hpp__ */
