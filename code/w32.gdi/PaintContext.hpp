#ifndef _w32_gdi_PaintContext_hpp__
#define _w32_gdi_PaintContext_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32.gdi/DeviceContext.hpp>

namespace w32{ namespace gdi {

    class Rectangle;
    class Window;

        /*!
         * @brief Wraps the context used during drawing operations.
         */
    class PaintContext :
        private NotCopyable
    {
        /* nested types. */
    private:
        typedef ::PAINTSTRUCT Data;

        /* data. */
    private:
        Data myData;
        DeviceContext myDevice;

        /* construction. */
    public:
        explicit PaintContext ( Window& window );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        DeviceContext device () const;

            /*!
             * @brief Ask if you should redraw the window's background.
             */
        bool erase () const;

            /*!
             * @brief Query what area we should redraw.
             */
        Rectangle area () const;
    };

} }

#endif /* _w32_gdi_PaintContext_hpp__ */
