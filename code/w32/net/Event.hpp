#ifndef _w32_net_Event_hpp__
#define _w32_net_Event_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/mt/ManualResetEvent.hpp>

namespace w32 { namespace net {

    class Socket;

    class Event
    {
        /* nested types. */
    public:
        typedef long Bitfield;

        /* values. */
    public:
        static const Event accept ();
        static const Event connect ();
        static const Event close ();
        static const Event get ();
        static const Event put ();
        static const Event oob ();

        /* data. */
    private:
        Bitfield myBits;

        /* construction. */
    private:
        Event ( Bitfield bits );

        /* methods. */
    public:
        Bitfield bits () const;

        /* operators. */
    public:
        operator Bitfield () const;
    };

    class Events
    {
        /* nested types.*/
    public:
        typedef ::WSANETWORKEVENTS Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Events ( Socket& socket, mt::ManualResetEvent& event );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        /* operators. */
    public:
        bool operator& ( Event event ) const;
    };

} }

#endif /* _w32_net_Event_hpp__ */
