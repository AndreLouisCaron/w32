// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.io/SerialPort.hpp>
#include <w32/Error.hpp>
#include <sstream>

namespace {

    ::HANDLE open ( const wchar_t * name )
    {
        const ::HANDLE result = ::CreateFileW(
            name, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0
            );
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_FILE_NOT_FOUND ) {
            }
            else if ( error == ERROR_PATH_NOT_FOUND ) {
            }
            else if ( error == ERROR_ACCESS_DENIED ) {
            }
            UNCHECKED_WIN32C_ERROR(CreateFile, error);
        }
        return (result);
    }

    ::HANDLE open ( int number )
    {
        std::wostringstream name;
        name << L"\\\\.\\COM" << number;
        return (open(name.str().c_str()));
    }

}

namespace w32 { namespace io {

    SerialPort::SerialPort
        ( const string& name, const Control& control, const Timeouts& timeouts )
        : Channel(claim(::open(name.data())))
    {
        configure(control);
        configure(timeouts);
    }

    SerialPort::SerialPort
        ( int number, const Control& control, const Timeouts& timeouts )
        : Channel(claim(::open(number)))
    {
        configure(control);
        configure(timeouts);
    }

    void SerialPort::configure ( const w32::io::SerialPort::Control &control )
    {
        const ::BOOL result = ::SetCommState(
            handle(), const_cast< ::LPDCB >(&control.data())
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetCommState, error);
        }
    }

    void SerialPort::configure ( const w32::io::SerialPort::Timeouts &timeouts )
    {
        const ::BOOL result = ::SetCommTimeouts(
            handle(), const_cast< ::LPCOMMTIMEOUTS >(&timeouts.data())
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetCommState, error);
        }
    }

    SerialPort::Control::Control ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.DCBlength = sizeof(myData);
        
            // Default to popular configuration.
        parity(Parity::none());
        rate(Rate::_9600());
        size(Size::_8());
        stop(Stop::_1());
        binary(true);
    }

    SerialPort::Control::Data& SerialPort::Control::data ()
    {
        return (myData);
    }

    const SerialPort::Control::Data& SerialPort::Control::data () const
    {
        return (myData);
    }

    void SerialPort::Control::parity ( const Parity& parity )
    {
        myData.Parity = parity;
        //myData.fParity = TRUE;?
    }

    SerialPort::Parity SerialPort::Control::parity () const
    {
        return (Parity::of(*this));
    }

    void SerialPort::Control::rate ( const Rate& rate )
    {
        myData.BaudRate = rate;
    }

    SerialPort::Rate SerialPort::Control::rate () const
    {
        return (Rate::of(*this));
    }

    void SerialPort::Control::size ( const Size& size )
    {
        myData.ByteSize = size;
    }

    SerialPort::Size SerialPort::Control::size () const
    {
        return (Size::of(*this));
    }

    void SerialPort::Control::stop ( const Stop& stop )
    {
        myData.StopBits = stop;
    }

    SerialPort::Stop SerialPort::Control::stop () const
    {
        return (Stop::of(*this));
    }

    void SerialPort::Control::binary ( bool binary )
    {
        myData.fBinary = binary? TRUE : FALSE;
    }

    bool SerialPort::Control::binary () const
    {
        return (myData.fBinary);
    }

    SerialPort::Timeouts::Timeouts ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        
            // Default to blocking read operations, just like sockets.
        myData.ReadIntervalTimeout = MAXDWORD;
    }

    SerialPort::Timeouts::Data& SerialPort::Timeouts::data ()
    {
        return (myData);
    }

    const SerialPort::Timeouts::Data& SerialPort::Timeouts::data () const
    {
        return (myData);
    }

    SerialPort::Parity SerialPort::Parity::none ()
    {
        return (NOPARITY);
    }

    SerialPort::Parity SerialPort::Parity::of ( const Control& control )
    {
        return (control.data().Parity);
    }

    SerialPort::Parity::Parity ( Value value )
        : myValue(value)
    {
    }

    SerialPort::Parity::Value SerialPort::Parity::value () const
    {
        return (myValue);
    }

    SerialPort::Parity::operator SerialPort::Parity::Value () const
    {
        return (value());
    }

    SerialPort::Rate SerialPort::Rate::_9600 ()
    {
        return (CBR_9600);
    }

    SerialPort::Rate SerialPort::Rate::of ( const Control& control )
    {
        return (control.data().BaudRate);
    }

    SerialPort::Rate::Rate ( Value value )
        : myValue(value)
    {
    }

    SerialPort::Rate::Value SerialPort::Rate::value () const
    {
        return (myValue);
    }

    SerialPort::Rate::operator SerialPort::Rate::Value () const
    {
        return (value());
    }

    SerialPort::Size SerialPort::Size::_8 ()
    {
        return (8);
    }

    SerialPort::Size SerialPort::Size::of ( const Control& control )
    {
        return (control.data().ByteSize);
    }

    SerialPort::Size::Size ( Value value )
        : myValue(value)
    {
    }

    SerialPort::Size::Value SerialPort::Size::value () const
    {
        return (myValue);
    }

    SerialPort::Size::operator SerialPort::Size::Value () const
    {
        return (value());
    }

    SerialPort::Stop SerialPort::Stop::_1 ()
    {
        return (ONESTOPBIT);
    }

    SerialPort::Stop SerialPort::Stop::of ( const Control& control )
    {
        return (control.data().StopBits);
    }

    SerialPort::Stop::Stop ( Value value )
        : myValue(value)
    {
    }

    SerialPort::Stop::Value SerialPort::Stop::value () const
    {
        return (myValue);
    }

    SerialPort::Stop::operator SerialPort::Stop::Value () const
    {
        return (value());
    }

} }
