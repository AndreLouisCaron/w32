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

#include <w32/strings.hpp>

namespace {

    void abandon ( wchar_t ** strings ) {}
    void destroy ( wchar_t ** strings )
    {
        // Where do we fetch size from? Use custom type?
    }

    w32::Reference< wchar_t** > empty ()
    {
        static wchar_t* data[] = { 0 };
        return (w32::Reference< wchar_t** >(data, &abandon));
    }

}

namespace w32 {

    strings::strings ()
        : myData(::empty())
    {
    }

    const wchar_t ** strings::data () const
    {
        return ((const wchar_t**)(wchar_t**)myData);
    }

    strings::iterator strings::begin () const
    {
        return (iterator(0));
    }

    strings::iterator strings::end () const
    {
        return (iterator(0));
    }

    strings::size_type strings::size () const
    {
        return (0);
    }

    strings::value_type strings::operator[] ( size_type i ) const
    {
        return (((wchar_t**)myData)[i]);
    }

    strings::iterator::iterator ( const wchar_t ** position )
        : myPosition(position)
    {
    }

    const wchar_t * strings::iterator::operator* () const
    {
        return (*myPosition);
    }

    strings::iterator& strings::iterator::operator++ ()
    {
        ++myPosition;
        return (*this);
    }

    strings::iterator strings::iterator::operator++ ( int )
    {
        iterator old(*this);
        ++(*this);
        return (old);
    }

    bool strings::iterator::operator== ( const iterator& other ) const
    {
        return (myPosition == other.myPosition);
    }

    bool strings::iterator::operator!= ( const iterator& other ) const
    {
        return (myPosition != other.myPosition);
    }

}
