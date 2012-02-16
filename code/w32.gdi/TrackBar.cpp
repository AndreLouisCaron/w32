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

#include <w32.gdi/TrackBar.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Window.hpp>
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
