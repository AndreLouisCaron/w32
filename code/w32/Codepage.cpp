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

#include <w32/Codepage.hpp>

namespace w32 {

    const Codepage Codepage::ansi ()
    {
        return (CP_ACP);
    }

    const Codepage Codepage::oem ()
    {
        return (CP_OEMCP);
    }

    const Codepage Codepage::utf7 ()
    {
        return (CP_UTF7);
    }

    const Codepage Codepage::utf8()
    {
        return (CP_UTF8);
    }

    Codepage::Codepage ( Value value )
        : myValue(value)
    {
    }

    bool Codepage::valid () const
    {
        return (::IsValidCodePage(myValue) != FALSE);
    }

    Codepage::Value Codepage::value () const
    {
        return (myValue);
    }

    Codepage::operator Value () const
    {
        return (myValue);
    }

    bool Codepage::operator== ( const Codepage& rhs ) const
    {
        return (value() == rhs.value());
    }

    bool Codepage::operator!= ( const Codepage& rhs ) const
    {
        return (value() != rhs.value());
    }

}
