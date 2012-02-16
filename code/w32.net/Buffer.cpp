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

#include <w32.net/Buffer.hpp>
#include <algorithm>

namespace w32 { namespace net {

    Buffer::Buffer ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Buffer::Buffer ( iterator begin, size_type size )
    {
        myData.buf = begin;
        myData.len = size;
    }

    Buffer::Buffer ( iterator begin, iterator end )
    {
        myData.buf = begin;
        myData.len = std::distance(begin, end);
    }

    Buffer::Data& Buffer::data ()
    {
        return (myData);
    }

    const Buffer::Data& Buffer::data () const
    {
        return (myData);
    }

    Buffer::iterator Buffer::begin ()
    {
        return (myData.buf);
    }

    Buffer::const_iterator Buffer::begin () const
    {
        return (myData.buf);
    }

    Buffer::iterator Buffer::end ()
    {
        return (myData.buf + myData.len);
    }

    Buffer::const_iterator Buffer::end () const
    {
        return (myData.buf + myData.len);
    }

} }
