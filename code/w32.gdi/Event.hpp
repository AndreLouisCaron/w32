#ifndef _w32_gdi_Event_hpp__
#define _w32_gdi_Event_hpp__

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

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32.gdi/Message.hpp>
#include <w32.gdi/Point.hpp>

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
