#ifndef _w32_net_Socket_HPP__
#define _w32_net_Socket_HPP__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/net/Context.hpp>
#include <w32/net/Event.hpp>

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
    protected:
        Socket ( Handle handle );

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

        void select ( mt::ManualResetEvent& event, Event events );
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
