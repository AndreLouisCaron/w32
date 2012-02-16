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

#include <w32.msi/Hash.hpp>
#include <w32/Error.hpp>
#include <iomanip>
#include <iostream>

namespace {

    ::MSIFILEHASHINFO compute ( const char * path )
    {
        ::MSIFILEHASHINFO hash = { sizeof(::MSIFILEHASHINFO), { 0, 0, 0, 0 } };
        const ::UINT result = ::MsiGetFileHashA(path,0,&hash);
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(MsiGetFileHash,result);
        }
        return (hash);
    }

    std::ostream& u32 ( std::ostream& out ) {
        return (out << std::hex << std::setfill('0') << std::setw(8));
    }

}

namespace w32 { namespace msi {

    Hash::Hash ( const char * path )
        : myValue(compute(path))
    {
    }

    Hash::Value& Hash::value ()
    {
        return (myValue);
    }

    const Hash::Value& Hash::value () const
    {
        return (myValue);
    }

    std::ostream& operator<< ( std::ostream& out, const Hash& hash )
    {
        out << u32 << hash.value().dwData[0]
            << u32 << hash.value().dwData[1]
            << u32 << hash.value().dwData[2]
            << u32 << hash.value().dwData[3];
        return (out);
    }

} }
