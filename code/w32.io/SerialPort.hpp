#ifndef _w32_io_SerialPort_hpp__
#define _w32_io_SerialPort_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/SerialPort.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
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

        void parity ( const Parity& parity );
        Parity parity () const;
        void rate ( const Rate& rate );
        Rate rate () const;
        void size ( const Size& size );
        Size size () const;
        void stop ( const Stop& stop );
        Stop stop () const;

        void binary ( bool binary );
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
