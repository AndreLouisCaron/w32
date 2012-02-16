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

#include <w32.net/Timespan.hpp>

namespace w32 { namespace net {

    Timespan::Timespan ()
    {
        ::ZeroMemory(&myValue, sizeof(myValue));
    }

    Timespan::Timespan ( const Value& value )
        : myValue(value)
    {
    }

    Timespan::Timespan ( long seconds, long microseconds )
    {
        myValue.tv_sec = seconds;
        myValue.tv_usec = microseconds;
    }

    Timespan::Value& Timespan::value ()
    {
        return (myValue);
    }

    const Timespan::Value& Timespan::value () const
    {
        return (myValue);
    }

    long Timespan::seconds () const
    {
        return (myValue.tv_sec);
    }

    void Timespan::seconds ( long value )
    {
        myValue.tv_sec = value;
    }

    long Timespan::microseconds () const
    {
        return (myValue.tv_usec);
    }

    void Timespan::microseconds ( long value )
    {
        myValue.tv_usec = value;
    }

} }
