#ifndef _w32_gdi_Event_hpp__
#define _w32_gdi_Event_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"
#include <w32/types.hpp>
#include <w32/gdi/Message.hpp>
#include <w32/gdi/Point.hpp>

namespace w32 { namespace gdi {

    class Event
    {
        /* nested types. */
    public:
        typedef ::MSG Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Event () {
            ::ZeroMemory(&myData, sizeof(myData));
        }

        Event ( const Data& data )
            : myData(data)
        {}

        /* methods. */
    public:
        Data& data () {
            return (myData);
        }

        const Data& data () const {
            return (myData);
        }

        Message message () const {
            return (Message(myData.message, wp(), lp()));
        }

        ::HWND window () const {
            return (myData.hwnd);
        }

        lparam lp () const {
            return (myData.lParam);
        }

        wparam wp () const {
            return (myData.wParam);
        }

        dword time () const {
            return (myData.time);
        }

        Point cursorposition () const {
            return (Point(myData.pt));
        }

        void translate () const {
            ::TranslateMessage(&myData);
        }

        void dispatch () const {
            ::DispatchMessage(&myData);
        }
    };

} }

#endif /* _w32_gdi_Event_hpp__ */
