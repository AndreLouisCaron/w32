// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
