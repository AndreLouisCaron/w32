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

#include <w32.gdi/Pen.hpp>
#include <w32.gdi/Color.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HPEN create ( ::COLORREF color, int width, int style )
    {
        const ::HPEN handle = ::CreatePen(style, width, color);
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePen, error);
        }
        return (handle);
    }

    ::HPEN fetch ( int pen )
    {
        const ::HGDIOBJ handle = ::GetStockObject(pen);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetStockObject, error);
        }
        return (::HPEN(handle));
    }

    void destroy ( ::HPEN object )
    {
        if ( ::DeleteObject(object) == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HPEN object )
    {
    }

}

namespace w32 { namespace gdi {

    Pen::Handle Pen::claim ( ::HPEN object )
    {
        return (Pen::Handle(object, &::destroy));
    }

    Pen::Handle Pen::proxy ( ::HPEN object )
    {
        return (Pen::Handle(object, &::abandon));
    }

    const Pen Pen::null ()
    {
        return (Pen(proxy(::fetch(NULL_PEN))));
    }

    const Pen Pen::white ()
    {
        return (Pen(proxy(::fetch(WHITE_PEN))));
    }

    const Pen Pen::black ()
    {
        return (Pen(proxy(::fetch(BLACK_PEN))));
    }

    Pen::Pen ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Pen::Pen ( const Color& color, int width, const Style& style )
        : myHandle(claim(::create(color.value(), width, style)))
    {
    }

    const Pen::Handle& Pen::handle () const
    {
        return (myHandle);
    }

    Pen::Style Pen::Style::solid ()
    {
        return (PS_SOLID);
    }

    Pen::Style Pen::Style::dash ()
    {
        return (PS_DASH);
    }

    Pen::Style Pen::Style::null ()
    {
        return (PS_NULL);
    }

    Pen::Style::Style ( Value value )
        : myValue(value)
    {
    }

    Pen::Style::operator Value () const
    {
        return (myValue);
    }

} }
