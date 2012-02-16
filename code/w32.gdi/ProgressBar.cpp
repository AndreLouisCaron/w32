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

#include <w32.gdi/ProgressBar.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32/string.hpp>

namespace {

    ::HWND create (
        ::DWORD extended, ::DWORD standard, ::HWND parent, const ::RECT& bounds
        )
    {
        const ::HWND handle = ::CreateWindowExW(
            extended, PROGRESS_CLASSW, 0, standard,
            bounds.left, bounds.top, bounds.right-bounds.left,
            bounds.bottom-bounds.top, parent, 0, ::GetModuleHandle(0), 0
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateWindowEx, error);
        }
        return (handle);
    }

}

namespace w32 { namespace gdi {

    ProgressBar::ProgressBar ( const Handle& handle )
        : Control(handle)
    {
    }

    ProgressBar::ProgressBar ( Window& window, const Rectangle& bounds )
        : Control(claim(
              ::create(0, WS_CHILD, window.handle(), bounds.data())
              ))
    {
    }

    int ProgressBar::displace ( int delta )
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), PBM_DELTAPOS, static_cast<::WPARAM>(delta), 0
            ));
        return(result);
    }

    int ProgressBar::next ()
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), PBM_STEPIT, 0, 0
            ));
        return(result);
    }

    int ProgressBar::position ( int value )
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), PBM_SETPOS, static_cast<::WPARAM>(value), 0
            ));
        return(result);
    }

    int ProgressBar::position () const
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), PBM_GETPOS, 0, 0
            ));
        return(result);
    }

    ProgressBar::Range ProgressBar::range ( const Range& value )
    {
        const ::LPARAM result = ::SendMessageW(
            handle(), PBM_SETRANGE, 0,
            MAKELPARAM(value.low(),value.high())
            );
        return (Range(LOWORD(result),HIWORD(result)));
    }

    int ProgressBar::step ( int delta )
    {
        const int result = static_cast<int>(::SendMessageW(
            handle(), PBM_SETSTEP, static_cast<::WPARAM>(delta), 0
            ));
        return(result);
    }

#if 0 // MSDN documentation labeled this as "not implemented".
        int ProgressBar::step () const
        {
            const int result = static_cast<int>(::SendMessageW(
                                                    handle(), PBM_GETSTEP, 0, 0
                                                ));
            return(result);
        }
#endif

    ProgressBar::Range::Range ()
    {
        myData.iLow = 0;
        myData.iHigh = 0;
    }

    ProgressBar::Range::Range ( int low, int high )
    {
        myData.iLow = low;
        myData.iHigh = high;
    }

    ProgressBar::Range::Range ( const ::PBRANGE& data )
        : myData(data)
    {
    }

    ::PBRANGE& ProgressBar::Range::get ()
    {
        return (myData);
    }

    const ::PBRANGE& ProgressBar::Range::get () const
    {
        return (myData);
    }

    int ProgressBar::Range::low () const
    {
        return (myData.iLow);
    }

    int ProgressBar::Range::high () const
    {
        return (myData.iHigh);
    }

    void ProgressBar::Range::low ( int value )
    {
        myData.iLow = value;
    }

    void ProgressBar::Range::high ( int value )
    {
        myData.iHigh = value;
    }

} }
