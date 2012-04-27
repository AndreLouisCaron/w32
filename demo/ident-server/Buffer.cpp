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
 * @file demo/ident/Buffer.cpp
 */

#include "Buffer.hpp"
#include <algorithm>

namespace idp {

    Buffer::Buffer ( w32::dword capacity )
        : mySize(capacity),
          myData(new w32::byte[mySize]),
          myLbnd(0), myUbnd(0)
    {
    }

    Buffer::~Buffer ()
    {
        delete [] myData;
        myData = 0;
        myUbnd = mySize = 0;
    }

    w32::dword Buffer::capacity () const
    {
        return (mySize);
    }

    void * Buffer::data ()
    {
        return (myData+myLbnd);
    }

    const void * Buffer::data () const
    {
        return (myData+myLbnd);
    }

    w32::dword Buffer::size () const
    {
        return (myUbnd - myLbnd);
    }

    void * Buffer::next ()
    {
        return (myData + myUbnd);
    }

    w32::dword Buffer::left () const
    {
        return (mySize - myUbnd);
    }

    void Buffer::took ( w32::dword used )
    {
        myLbnd = std::min(myLbnd+used, myUbnd);
    }

    void Buffer::gave ( w32::dword used )
    {
        myUbnd = std::min(myUbnd+used, mySize);
    }

    bool Buffer::full () const
    {
        return (myUbnd == mySize);
    }

    bool Buffer::empty () const
    {
        return (myLbnd == myUbnd);
    }

    void Buffer::pack ()
    {
        std::copy(myData+myLbnd, myData+myUbnd, myData);
        myUbnd = myUbnd - myLbnd, myLbnd = 0;
    }

    bool Buffer::packed () const
    {
        return (myLbnd == 0);
    }

    void Buffer::clear ()
    {
        myUbnd = myLbnd = 0;
    }

    void Buffer::clear ( bool erase )
    {
        if (erase) {
            this->erase();
        }
        clear();
    }

    void Buffer::erase ()
    {
        ::ZeroMemory(myData, mySize);
    }

    void Buffer::put ( const w32::byte * data, w32::dword size )
    {
        std::copy(data, data+size, myData+myLbnd), myUbnd += size;
    }

    void Buffer::put ( const void * data, w32::dword size )
    {
        put(static_cast<const w32::byte*>(data), size);
    }

    void Buffer::put ( const std::string& payload )
    {
        put(payload.data(), payload.size());
    }

}
