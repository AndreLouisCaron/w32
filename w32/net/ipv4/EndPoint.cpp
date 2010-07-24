/*!
 * @file w32/net/ipv4/EndPoint.cpp
 * @author Andre Caron
 */

#include <w32/net/ipv4/EndPoint.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace w32 {
    namespace net {
        namespace ipv4 {

            EndPoint::EndPoint ()
            {
                ::ZeroMemory(&myData, sizeof(myData));
                myData.sin_family = AF_INET;
            }

            EndPoint::EndPoint ( const Data& address )
            {
                ::ZeroMemory(&myData, sizeof(myData));
                myData.sin_family = AF_INET;
            }

            EndPoint::EndPoint ( uint32 address, uint16 port )
            {
                ::ZeroMemory(&myData, sizeof(myData));
                myData.sin_family = AF_INET;
                myData.sin_addr.S_un.S_addr = address.raw();
                myData.sin_port = port.raw();
            }

            EndPoint::EndPoint ( uint8 b1, uint8 b2, uint8 b3, uint8 b4, uint16 port )
            {
                ::ZeroMemory(&myData, sizeof(myData));
                myData.sin_family = AF_INET;
                myData.sin_addr.S_un.S_un_b.s_b1 = b1;
                myData.sin_addr.S_un.S_un_b.s_b2 = b2;
                myData.sin_addr.S_un.S_un_b.s_b3 = b3;
                myData.sin_addr.S_un.S_un_b.s_b4 = b4;
                myData.sin_port = port.raw();
            }

            EndPoint::EndPoint ( const Address& address, uint16 port )
            {
                ::ZeroMemory(&myData, sizeof(myData));
                myData.sin_family = AF_INET;
                myData.sin_addr.S_un.S_addr = address.value().S_un.S_addr;
                myData.sin_port = port.raw();
            }

            EndPoint::Data& EndPoint::data ()
            {
                return (myData);
            }

            const EndPoint::Data& EndPoint::data () const
            {
                return (myData);
            }

            uint16 EndPoint::port () const
            {
                return (uint16(uint16::box(myData.sin_port)));
            }

            Address EndPoint::address () const
            {
                return (Address(uint32(uint32::box(myData.sin_addr.S_un.S_addr))));
            }

            std::ostream& operator<< ( std::ostream& out, const EndPoint& value )
            {
                return (out << value.address() << ':' << value.port());
            }

        }
    }
}
