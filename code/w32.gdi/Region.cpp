// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.gdi/Region.hpp>
#include <w32.gdi/Point.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Size.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    void destroy ( ::HRGN object )
    {
        const ::BOOL result = ::DeleteRgn(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HRGN object )
    {
    }

}

namespace w32 { namespace gdi {

    Region::Handle Region::claim ( ::HRGN object )
    {
        return (Handle(object, &::destroy));
    }

    Region::Handle Region::proxy ( ::HRGN object )
    {
        return (Handle(object, &::abandon));
    }

    Region::Region ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Region::Handle& Region::handle () const
    {
        return (myHandle);
    }

    Region Region::rectangle ( const Rectangle& area )
    {
        const ::HRGN handle = ::CreateRectRgnIndirect(&area.data());
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateRectRgnIndirect, error);
        }
        return (Region(claim(handle)));
    }

    Region Region::rounded ( const Rectangle& area, const Size& size )
    {
        const ::HRGN handle = ::CreateRoundRectRgn(
            area.left(), area.top(), area.right(),
            area.bottom(), size.width(), size.height()
            );
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateRoundRectRgn, error);
        }
        return (Region(claim(handle)));
    }

    Region Region::ellipse ( const Rectangle& area )
    {
        const ::HRGN handle = ::CreateEllipticRgnIndirect(&area.data());
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateEllipticRgnIndirect, error);
        }
        return (Region(claim(handle)));
    }

    Region Region::polygon ( const Point * vertices, int count )
    {
        const ::HRGN handle = ::CreatePolygonRgn(
            reinterpret_cast< const::POINT* >(vertices), count, WINDING);
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePolygonRgn, error);
        }
        return (Region(claim(handle)));
    }

    void Region::offset ( int x, int y )
    {
        if ( ::OffsetRgn(myHandle, x, y) == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EqualRgn, error);
        }
    }

    Rectangle Region::box () const
    {
        Rectangle area;
        if ( ::GetRgnBox(myHandle, &area.data()) == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetRgnBox, error);
        }
        return (area);
    }

    bool Region::contains ( const Point& point ) const
    {
        const ::BOOL result = ::PtInRegion(
            myHandle, point.x(), point.y()
            );
        return (result == TRUE);
    }

    Region& Region::operator-= ( const Region& other )
    {
        const int result = ::CombineRgn(
            handle(), handle(), other.handle(), RGN_DIFF
            );
        if ( result == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CombineRgn, error);
        }
        return (*this);
    }

    Region& Region::operator|= ( const Region& other )
    {
        const int result = ::CombineRgn(
            handle(), handle(), other.handle(), RGN_OR
            );
        if ( result == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CombineRgn, error);
        }
        return (*this);
    }

    Region& Region::operator&= ( const Region& other )
    {
        const int result = ::CombineRgn(
            handle(), handle(), other.handle(), RGN_AND
            );
        if ( result == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CombineRgn, error);
        }
        return (*this);
    }

    Region& Region::operator^= ( const Region& other )
    {
        const int result = ::CombineRgn(
            handle(), handle(), other.handle(), RGN_XOR
            );
        if ( result == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CombineRgn, error);
        }
        return (*this);
    }

    bool Region::operator== ( const Region& other ) const
    {
        const ::BOOL result = ::EqualRgn(
            myHandle, other.myHandle
            );
        if ( result == ERROR ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EqualRgn, error);
        }
        return (result == TRUE);
    }


} }
