/*!
 * @file EndPoint.cpp
 * @author Andre Caron
 */

#include <win32c/net/ipv6/EndPoint.hpp>
#include <win32c/diagnostics/UncheckedError.hpp>
#include <iostream>

namespace win32c {
    namespace net {
        namespace ipv6 {

            EndPoint::EndPoint ()
            {
                ::memset(&myValue,0,sizeof(myValue));
                myValue.sin_family = AF_INET6;
            }

            EndPoint::EndPoint ( const ::sockaddr_in6& address )
            {
                ::memcpy(&myValue,&address,sizeof(myValue));
                myValue.sin_family = AF_INET6;
            }

            ::sockaddr_in6& EndPoint::value ()
            {
                return (myValue);
            }

            const ::sockaddr_in6& EndPoint::value () const
            {
                return (myValue);
            }

        }
    }
}
