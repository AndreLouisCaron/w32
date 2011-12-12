// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Brush.hpp>
#include <w32.gdi/Color.hpp>
#include <w32.gdi/SystemColor.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HBRUSH create ( ::COLORREF color )
    {
        const ::HBRUSH handle = ::CreateSolidBrush(color);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateSolidBrush, error);
        }
        return (handle);
    }

    ::HBRUSH fetch_system ( int color )
    {
        const ::HBRUSH handle = ::GetSysColorBrush(color);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetSysColorBrush, error);
        }
        return (handle);
    }

    ::HBRUSH fetch ( int brush )
    {
        const ::HGDIOBJ handle = ::GetStockObject(brush);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetStockObject, error);
        }
        return (::HBRUSH(handle));
    }

    void destroy ( ::HBRUSH object )
    {
        if ( ::DeleteObject(object) == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HBRUSH object )
    {
    }

}

namespace w32 { namespace gdi {

    Brush::Handle Brush::claim ( ::HBRUSH object )
    {
        return (Brush::Handle(object, &::destroy));
    }

    Brush::Handle Brush::proxy ( ::HBRUSH object )
    {
        return (Brush::Handle(object, &::abandon));
    }

    const Brush Brush::null ()
    {
        return (Brush(proxy(::fetch(NULL_BRUSH))));
    }

    const Brush Brush::white ()
    {
        return (Brush(proxy(::fetch(WHITE_BRUSH))));
    }

    const Brush Brush::lightGray ()
    {
        return (Brush(proxy(::fetch(LTGRAY_BRUSH))));
    }

    const Brush Brush::gray ()
    {
        return (Brush(proxy(::fetch(GRAY_BRUSH))));
    }

    const Brush Brush::darkGray ()
    {
        return (Brush(proxy(::fetch(DKGRAY_BRUSH))));
    }

    const Brush Brush::black ()
    {
        return (Brush(proxy(::fetch(BLACK_BRUSH))));
    }

    Brush::Brush ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Brush::Brush ( const Color& color )
        : myHandle(claim(::create(color.value())))
    {
    }

    Brush::Brush ( const SystemColor& color )
        : myHandle(proxy(::fetch_system(color)))
    {
    }

    const Brush::Handle& Brush::handle () const
    {
        return (myHandle);
    }

} }
