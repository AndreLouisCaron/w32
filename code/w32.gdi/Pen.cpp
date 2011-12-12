// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
