#ifndef _w32_gdi_Cursor_hpp__
#define _w32_gdi_Cursor_hpp__

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
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/NotCopyable.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Image displayed where the mouse currently points.
         */
    class Cursor
    {
        /* nested types. */
    public:
        typedef Reference< ::HCURSOR, void(*)(::HCURSOR) > Handle;

        class Show;
        class Hide;

        /* class methods. */
    public:
        static Handle claim ( ::HCURSOR object );
        static Handle proxy ( ::HCURSOR object );

        /* class data. */
    public:
        static const Cursor appstarting ();
        static const Cursor arrow ();
        static const Cursor cross ();
        static const Cursor hand ();
        static const Cursor no ();
        static const Cursor ibeam ();
        static const Cursor sizeall ();
        static const Cursor sizenesw ();
        static const Cursor sizens ();
        static const Cursor sizenwse ();
        static const Cursor sizewe ();
        static const Cursor up ();
        static const Cursor wait ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Cursor ( const Handle& handle );
        explicit Cursor ( const string& path );

        /* methods. */
    public:
            /*!
             * @brief Obtains the cursor's handle.
             */
        const Handle& handle () const;
    };

    class Cursor::Show :
        private NotCopyable
    {
        /* construction. */
    public:
        Show () {
            ::ShowCursor(TRUE);
        }

        ~Show () {
            ::ShowCursor(FALSE);
        }
    };

    class Cursor::Hide :
        private NotCopyable
    {
        /* construction. */
    public:
        Hide () {
            ::ShowCursor(FALSE);
        }

        ~Hide () {
            ::ShowCursor(TRUE);
        }
    };

} }

#endif /* _w32_gdi_Cursor_hpp__ */
