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

#include <w32.net/Set.hpp>
#include <w32/Error.hpp>
#include <algorithm>

namespace {

    const char RangeErrorMessage[] =
        "File descriptor sets have limited capacity!";

}

namespace w32 { namespace net {

    Set::Set ()
    {
            // Make sure no sockets are accidentally referenced.
        clear();
    }

    Set::~Set ()
    {
            // Make sure no sockets are accidentally referenced.
        clear();
    }

    Set::Data& Set::data ()
    {
        return (myData);
    }

    const Set::Data& Set::data () const
    {
        return (myData);
    }

    Set::size_type Set::size () const
    {
        return (myData.fd_count);
    }

    bool Set::empty () const
    {
        return (size() == 0);
    }

    bool Set::full () const
    {
        return (size() == capacity());
    }

    void Set::clear ()
    {
            // The set is currently empty.
        myData.fd_count = 0;
        
            // Make sure no accidents could happen.
        std::fill(begin(), end(), INVALID_SOCKET);
    }

    Set::size_type Set::capacity ()
    {
        return (FD_SETSIZE);
    }

    void Set::add ( const Socket& socket )
    {
            // Sanity check, don't insert twice.
        if ( contains(socket) ) {
            return;
        }
        
            // Bound check.
        if ( size() == capacity() ) {
            throw (std::range_error(RangeErrorMessage));
        }
        
            // Insert element at the end.
        myData.fd_array[myData.fd_count++] = socket.handle();
    }

    bool Set::contains ( const Socket& socket ) const
    {
        const const_iterator match =
            std::find(begin(), end(), socket.handle());
        return (match != end());
    }

    void Set::remove ( const Socket& socket )
    {
            // Look for the requested element.
        const iterator match =
            std::find(begin(), end(), socket.handle());
        
            // Ignore requests to remove invalid values.
        if ( match != end() )
        {
                // Keep elements at the beginning of the range.
            std::copy(match+1, end(), match);
            
                // Make sure the last element is not referenced.
            myData.fd_array[--myData.fd_count] = INVALID_SOCKET;
        }
    }

    Set::iterator Set::begin ()
    {
        return (myData.fd_array);
    }

    Set::iterator Set::end ()
    {
        return (begin() + size());
    }

    Set::const_iterator Set::begin () const
    {
        return (myData.fd_array);
    }

    Set::const_iterator Set::end () const
    {
        return (begin() + size());
    }

} }
