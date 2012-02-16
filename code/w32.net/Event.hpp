#ifndef _w32_net_Event_hpp__
#define _w32_net_Event_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32.mt/ManualResetEvent.hpp>

namespace w32 { namespace net {

    class Socket;

    /*!
     * @ingroup w32-net
     */
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
