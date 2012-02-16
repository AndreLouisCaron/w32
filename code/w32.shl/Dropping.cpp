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

#include <w32.shl/Dropping.hpp>

namespace w32 { namespace shl {

    Dropping::Dropping ( const Data& data )
        : myDrop(0), myIndex(0)
    {
            // Ask for the list of files.
        ::FORMATETC format;
        format.cfFormat = CF_HDROP;
        format.ptd = 0;
        format.dwAspect = DVASPECT_CONTENT;
        format.lindex = -1;
        format.tymed = TYMED_HGLOBAL;
        
            // Obtain the medium to the dropped data.
        myMedium.tymed = TYMED_HGLOBAL;
        myMedium.hGlobal = 0;
        myMedium.pUnkForRelease = 0;
        data.get(format,myMedium);
        
            // Gain access to the description of the dropped data.
        myDrop = reinterpret_cast<::HDROP>(::GlobalLock(myMedium.hGlobal));
    }

    Dropping::~Dropping ()
    {
        ::GlobalUnlock(myMedium.hGlobal);
        ::ReleaseStgMedium(&myMedium);
    }

    uint Dropping::count () const
    {
        return (::DragQueryFileW(myDrop,0xFFFFFFFF,0,0));
    }

    const string Dropping::operator[] ( w32::dword index ) const
    {
        const w32::uint length = ::DragQueryFileW(myDrop,index,0,0);
        string result(length+1,'\0');
        const w32::uint written = ::DragQueryFileW(
            myDrop, index, const_cast<wchar_t*>(result.data()), length+1
            );
        result.resize(length);
        return (result);
    }

} }
