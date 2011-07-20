// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/TrackBar.hpp>
#include <w32/gdi/Rectangle.hpp>
#include <w32/gdi/Window.hpp>
#include <w32/Error.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, TRACKBAR_CLASSW, 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreateWindowEx,::GetLastError());
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    TrackBar::TrackBar ( const Handle& handle )
        : Control(handle)
    {
    }

    TrackBar::TrackBar ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    void TrackBar::clearTicks ( bool redraw )
    {
        ::SendMessageW(
            handle(), TBM_CLEARSEL,
            static_cast<::WPARAM>(redraw? TRUE:FALSE), 0
            );
    }

    Rectangle TrackBar::channelArea () const
    {
        ::RECT area;
        ::SendMessageW(
            handle(), TBM_GETCHANNELRECT, 0,
            reinterpret_cast<::LPARAM>(&area)
            );
        return (Rectangle(area));
    }

    int TrackBar::tickCount () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETNUMTICS, 0, 0
            );
        return (static_cast<int>(result));
    }

#if 0 // Totally unsafe...

    const ::DWORD * TrackBar::ticks () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETPTICKS, 0, 0
            );
        return (reinterpret_cast<const ::DWORD*>(result));
    }

#endif

    int TrackBar::minimum () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETRANGEMIN, 0, 0
            );
        return (static_cast<int>(result));
    }

    void TrackBar::minimum ( int value, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETRANGEMIN,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(value)
            );
    }

    int TrackBar::maximum () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETRANGEMAX, 0, 0
            );
        return (static_cast<int>(result));
    }

    void TrackBar::maximum ( int value, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETRANGEMAX,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(value)
            );
    }

    int TrackBar::position () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETPOS, 0, 0
            );
        return (static_cast<int>(result));
    }

    void TrackBar::position ( int value, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETPOS,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(value)
            );
    }

    void TrackBar::tickFrequency ( int frequency )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETTICFREQ,
            static_cast<::WPARAM>(frequency), 0
            );
    }

    void TrackBar::clearSelectionRange ()
    {
        ::SendMessageW(handle(),TBM_CLEARSEL,0,0);
    }

    int TrackBar::selectionStart () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETSELSTART, 0, 0
            );
        return (static_cast<int>(result));
    }

    void TrackBar::selectionStart ( int value, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETSELSTART,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(value)
            );
    }

    int TrackBar::selectionEnd () const
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_GETSELEND, 0, 0
            );
        return (static_cast<int>(result));
    }

    void TrackBar::selectionEnd ( int value, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETSELEND,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(value)
            );
    }

    void TrackBar::selection ( int start, int end, bool redraw )
    {
        const ::LRESULT result = ::SendMessageW(
            handle(), TBM_SETSEL,
            static_cast<::WPARAM>(redraw? TRUE:FALSE),
            static_cast<::LPARAM>(MAKELONG(start,end))
            );
    }

} }
