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

#include <w32.fs/Attributes.hpp>

namespace w32 { namespace fs {

    Attributes::Attributes ( const ::DWORD& flags )
        : myFlags(flags)
    {
    }

    Attributes::Attributes ( const string& path )
        : myFlags(::GetFileAttributesW(path.c_str()))
    {
    }

    const ::DWORD & Attributes::flags () const
    {
        return (myFlags);
    }

    bool Attributes::invalid () const
    {
        return (myFlags == INVALID_FILE_ATTRIBUTES);
    }

    bool Attributes::archive () const
    {
        return ((myFlags & FILE_ATTRIBUTE_ARCHIVE) != 0);
    }

    bool Attributes::compressed () const
    {
        return ((myFlags & FILE_ATTRIBUTE_COMPRESSED) != 0);
    }

    bool Attributes::folder () const
    {
        return ((myFlags & FILE_ATTRIBUTE_DIRECTORY) != 0);
    }

    bool Attributes::encrypted () const
    {
        return ((myFlags & FILE_ATTRIBUTE_ENCRYPTED) != 0);
    }

    bool Attributes::hidden () const
    {
        return ((myFlags & FILE_ATTRIBUTE_HIDDEN) != 0);
    }

    bool Attributes::normal () const
    {
        return ((myFlags & FILE_ATTRIBUTE_NORMAL) != 0);
    }

    bool Attributes::offline () const
    {
        return ((myFlags & FILE_ATTRIBUTE_OFFLINE) != 0);
    }

    bool Attributes::readonly () const
    {
        return ((myFlags & FILE_ATTRIBUTE_READONLY) != 0);
    }

    bool Attributes::reparsepoint () const
    {
        return ((myFlags & FILE_ATTRIBUTE_REPARSE_POINT) != 0);
    }

    bool Attributes::sparse () const
    {
        return ((myFlags & FILE_ATTRIBUTE_SPARSE_FILE) != 0);
    }

    bool Attributes::system () const
    {
        return ((myFlags & FILE_ATTRIBUTE_SYSTEM) != 0);
    }

    bool Attributes::temporary () const
    {
        return ((myFlags & FILE_ATTRIBUTE_TEMPORARY) != 0);
    }

    bool Attributes::operator== ( const Attributes& other ) const
    {
        return (myFlags == other.myFlags);
    }

    bool Attributes::operator!= ( const Attributes& other ) const
    {
        return (myFlags != other.myFlags);
    }

    bool exists ( const string& path )
    {
        const Attributes attributes(path);
        return (!attributes.invalid());
    }

} }
