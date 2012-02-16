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

#include <w32.shl/Location.hpp>

namespace w32 { namespace shl {

    const Location Location::computer ()
    {
        return (CSIDL_DRIVES);
    }

    const Location Location::desktop ()
    {
        return (CSIDL_DESKTOPDIRECTORY);
    }

    const Location Location::fonts ()
    {
        return (CSIDL_FONTS);
    }

    const Location Location::programs ()
    {
        return (CSIDL_PROGRAMS);
    }

    const Location Location::start ()
    {
        return (CSIDL_STARTMENU);
    }

    const Location Location::startup ()
    {
        return (CSIDL_STARTUP);
    }

    const Location Location::system ()
    {
        return (CSIDL_SYSTEM);
    }

    const Location Location::windows ()
    {
        return (CSIDL_WINDOWS);
    }

    Location::Location ( Value value )
        : myValue(value)
    {
    }

    Location::Value Location::value () const
    {
        return (myValue);
    }

    Location::operator Location::Value () const
    {
        return (myValue);
    }

    Location::operator Path () const
    {
        ::LPITEMIDLIST path = 0;
        const com::Result result = ::SHGetFolderLocation(
            0, myValue, 0, 0, &path
            );
        if ( result.bad() ) {
            throw std::exception("SHGetFolderLocation");
        }
        return (Path::box(path));
    }

} }
