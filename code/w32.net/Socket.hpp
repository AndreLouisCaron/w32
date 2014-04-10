#ifndef _w32_net_Socket_HPP__
#define _w32_net_Socket_HPP__

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
#include <w32/Reference.hpp>
#include <w32.io/Transfer.hpp>
#include <w32.net/Context.hpp>
#include <w32.net/Event.hpp>

namespace w32 { namespace net {

    class Socket
    {
        /* nested types. */
    public:
        typedef Reference< ::SOCKET > Handle;

            /*!
             * @brief Enumeration of socket types.
             */
        class Type;

            /*!
             * @brief Enumeration of socket shutdown modes.
             */
        class Shutdown;

        /* class methods. */
    public:
        static Handle claim ( ::SOCKET object );
        static Handle proxy ( ::SOCKET object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Socket ( Handle handle );

    public:
        virtual ~Socket ();

        /* methods. */
    public:
        const Handle& handle () const;

        void blocking ( bool blocking );
        ulong available () const;

            /*!
             * @brief Shuts down output through the socket.
             */
        void shutdown ();
        void shutdown ( const Shutdown& method );

        /*!
         * @brief Request that @a event be signalled when one of @a events occurs.
         *
         * @note Network events are level-triggered: the signaling state is
         *  held until the event is serviced.  For example, if an incoming
         *  connection is established, an `accept` event will be recorded even
         *  if the application doesn't have a pending accept operation; as soon
         *  as the application issues an accept request, @a event will be
         *  signaled so that the application knows that an incoming connection
         *  is ready.
         *
         * @see http://msdn.microsoft.com/en-us/library/ms741576.aspx
         * @see http://en.wikipedia.org/wiki/Interrupt#Level-triggered
         */
        void select ( mt::ManualResetEvent& event, Event events );

        /*!
         * @warning This seems to be completely broken in WinSock2.
         */
        void dontlinger ();

        /*!
         * @warning This seems to be completely broken in WinSock2.
         */
        void linger ( w32::uint16 seconds );

        ::LPFN_DISCONNECTEX disconnect_ex () const;

        void disconnect ( bool reuse=false );
        bool disconnect ( io::Transfer& transfer, bool reuse=false );
        bool disconnect ( ::OVERLAPPED& transfer, bool reuse=false );
    };

    class Socket::Type
    {
        /* class data. */
    public:
            /*! Sequenceed, reliable, two-way, connection based byte streams. */
        static const Type stream ();

            /*! Connection-less unreliable buffers of fixed maximum length. */
        static const Type dgram ();

            /*! Allows to manipulate the higher-level protocol header. */
        static const Type raw ();

            /*! Reliable message datagram. */
        static const Type rdm ();

            /*! Pseudo-streamed packets based on datagrams. */
        static const Type seqpacket ();

        /* nested types. */
    public:
        typedef int Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

    class Socket::Shutdown
    {
        /* class data. */
    public:
        static const Shutdown output ();
        static const Shutdown input ();
        static const Shutdown both ();

        /* nested types. */
    public:
        typedef int Value;

        /* data. */
    private:
        Value myValue;

    private:
        Shutdown ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

} }

#endif /* _w32_net_Socket_HPP__ */
