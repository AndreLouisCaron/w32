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

#include <w32.rgs/Access.hpp>

namespace w32 { namespace rgs {

    const Access Access::list ()
    {
        return (KEY_ENUMERATE_SUB_KEYS);
    }

    const Access Access::get ()
    {
        return (KEY_QUERY_VALUE);
    }

    const Access Access::set ()
    {
        return (KEY_SET_VALUE);
    }

    const Access Access::create ()
    {
        return (KEY_CREATE_SUB_KEY);
    }

    const Access Access::read ()
    {
        return (get()|list());
    }

    const Access Access::write ()
    {
        return (set()|create());
    }

    const Access Access::all ()
    {
        return (KEY_ALL_ACCESS);
    }

    Access::Access ( Value value )
        : myValue(value)
    {
    }

    Access::Value Access::value () const
    {
        return (myValue);
    }

    Access& Access::operator|= ( const Access& other )
    {
        myValue |= other.myValue;
        return (*this);
    }

    Access Access::operator| ( const Access& other ) const
    {
        Access result(*this);
        result |= other;
        return (result);
    }

    Access& Access::operator&= ( const Access& other )
    {
        myValue &= other.myValue;
        return (*this);
    }

    Access Access::operator& ( const Access& other ) const
    {
        Access result(*this);
        result &= other;
        return (result);
    }

    Access::operator Access::Value () const
    {
        return (value());
    }

} }
