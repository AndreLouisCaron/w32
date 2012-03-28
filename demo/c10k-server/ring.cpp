// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "ring.hpp"
#include <algorithm>

namespace server {

    ring::ring ( byte* lptr, byte* uptr )
        : myLPtr(lptr), myUPtr(uptr),
          myGPtr(myLPtr), myPPtr(myLPtr)
    {
    }

    std::size_t ring::size () const
    {
        if ( myGPtr <= myPPtr )
        {
            return (myPPtr - myGPtr);
        }
        else
        {
            return ((myUPtr - myGPtr) + (myPPtr - myLPtr));
        }
    }

    std::size_t ring::capacity () const
    {
        return (myUPtr - myLPtr);
    }

    bool ring::empty () const
    {
        return (myGPtr == myPPtr);
    }

    bool ring::full () const
    {
        return (size() == capacity());
    }

    byte * ring::put ( byte * lower, byte * upper )
    {
        if ( myPPtr < myGPtr )
        {
            while ((myPPtr < myGPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
        }
        else
        {
            while ((myPPtr < myUPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
            if ((myPPtr == myUPtr) && (myGPtr != myLPtr)) {
                myPPtr = myLPtr;
            }
            while ((myPPtr < myGPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
        }
        return (lower);
    }

    const byte * ring::put ( const byte * lower, const byte * upper )
    {
        if ( myPPtr < myGPtr )
        {
            while ((myPPtr < myGPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
        }
        else
        {
            while ((myPPtr < myUPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
            if ((myPPtr == myUPtr) && (myGPtr != myLPtr)) {
                myPPtr = myLPtr;
            }
            while ((myPPtr < myGPtr) && (lower < upper)) {
                *myPPtr++ = *lower++;
            }
        }
        return (lower);
    }

    byte * ring::get ( byte * lower, byte * upper )
    {
        if ( myGPtr <= myPPtr )
        {
            while ((myGPtr < myPPtr) && (lower < upper)) {
                *lower++ = *myGPtr++;
            }
        }
        else
        {
            while ((myGPtr < myUPtr) && (lower < upper)) {
                *lower++ = *myGPtr++;
            }
            if ( myGPtr == myUPtr ) {
                myGPtr = myLPtr;
            }
            while ((myGPtr < myPPtr) && (lower < upper)) {
                *lower++ = *myGPtr++;
            }
        }
        return (lower);
    }

    std::size_t ring::peek ( byte item ) const
    {
        const byte * gptr = myGPtr;
        if ( gptr <= myPPtr )
        {
            while ((gptr < myPPtr) && (*gptr != item)) {
                gptr++;
            }
        }
        else
        {
            while ((gptr < myUPtr) && (*gptr != item)) {
                gptr++;
            }
            if ( gptr == myUPtr ) {
                gptr = myLPtr;
            }
            while ((gptr < myPPtr) && (*gptr != item)) {
                gptr++;
            }
        }
        if ( gptr == myPPtr ) {
            return (0);
        }
        return (std::distance(static_cast<const byte*>(myGPtr), gptr+1));
    }

    std::size_t ring::put ( byte * data, std::size_t size )
    {
        return (put(data, data+size) - data);
    }

    std::size_t ring::get ( byte * data, std::size_t size )
    {
        return (get(data, data+size) - data);
    }

    std::size_t ring::put ( void * data, std::size_t size )
    {
        return (put(static_cast<byte*>(data), size));
    }

    std::size_t ring::get ( void * data, std::size_t size )
    {
        return (get(static_cast<byte*>(data), size));
    }

}
