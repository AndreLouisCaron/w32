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
