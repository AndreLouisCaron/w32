/*!
 * @file EndPoint.cpp
 * @author Andre Caron
 */

#include <w32.net.ipv6/EndPoint.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace w32 { namespace net { namespace ipv6 {

    EndPoint::EndPoint ()
    {
        ::memset(&myValue,0,sizeof(myValue));
        myValue.sin6_family = AF_INET6;
    }

    EndPoint::EndPoint ( const ::sockaddr_in6& address )
    {
        ::memcpy(&myValue,&address,sizeof(myValue));
        myValue.sin6_family = AF_INET6;
    }

    ::sockaddr_in6& EndPoint::value ()
    {
        return (myValue);
    }

    const ::sockaddr_in6& EndPoint::value () const
    {
        return (myValue);
    }

} } }
