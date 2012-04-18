#ifndef _w32_io_SerialPort_hpp__
#define _w32_io_SerialPort_hpp__

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

/*!
 * @file w32.io/SerialPort.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
#include <w32/Timespan.hpp>
#include <w32.io/Channel.hpp>

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     */
    class SerialPort :
        public Channel
    {
        /* nested types. */
    public:
        class Parity;
        class Stop;
        class Rate;
        class Control;
        class Size;
        class Timeouts;

        /* construction. */
    public:
        explicit SerialPort (
            const string& name, const Control& control, const Timeouts& timeouts
            );
        explicit SerialPort
            ( int number, const Control& control, const Timeouts& timeouts );

        /* methods. */
    private:
            // Keep these private: the port can only be configure once!
        void configure ( const Control& control );
        void configure ( const Timeouts& timeouts );
    };

    class SerialPort::Control :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::DCB Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Control ();
        Control ( const Data& data );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        Control& parity ( const Parity& parity );
        Parity parity () const;
        Control& rate ( const Rate& rate );
        Rate rate () const;
        Control& size ( const Size& size );
        Size size () const;
        Control& stop ( const Stop& stop );
        Stop stop () const;

        Control& binary ( bool binary );
        bool binary () const;
    };

    class SerialPort::Timeouts :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::COMMTIMEOUTS Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Timeouts ();
        Timeouts ( const Data& data );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        Timespan read_timeout () const;
        Timeouts& read_timeout ( Timespan timeout );
        Timeouts& blocking_read ();
    };

    class SerialPort::Parity
    {
        /* nested types. */
    public:
        typedef ::BYTE Value;

        /* values. */
    public:
        static Parity none ();

        /* class methods. */
    public:
        static Parity of ( const Control& control );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Parity ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

    class SerialPort::Rate
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* values. */
    public:
        static Rate _9600 ();

        /* class methods. */
    public:
        static Rate of ( const Control& control );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Rate ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

    class SerialPort::Size
    {
        /* nested types. */
    public:
        typedef ::BYTE Value;

        /* values. */
    public:
        static Size _8 ();

        /* class methods. */
    public:
        static Size of ( const Control& control );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Size ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

    class SerialPort::Stop
    {
        /* nested types. */
    public:
        typedef ::BYTE Value;

        /* values. */
    public:
        static Stop _1 ();

        /* data. */
    private:
        Value myValue;

        /* class methods. */
    public:
        static Stop of ( const Control& control );

        /* construction. */
    private:
        Stop ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

} }

#endif /* _w32_io_SerialPort_hpp__ */
