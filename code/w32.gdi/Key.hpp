#ifndef _w32_gdi_Key_hpp__
#define _w32_gdi_Key_hpp__

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

namespace w32 { namespace gdi {

    class KeyboardNotification;

    class Key
    {
        // Need to parse keycode from keyboard notification.
    friend class KeyboardNotification;

        /* class data. */
    public:
        static const Key shift ();
        static const Key lshift ();
        static const Key rshift ();
        static const Key control ();
        static const Key lcontrol ();
        static const Key rcontrol ();
        static const Key menu ();
        static const Key lmenu ();
        static const Key rmenu ();

        /* data. */
    private:
        int myIdentifier;

        /* construction. */
    private:
        Key ( int identifier );

        /* class methods. */
    public:
        static bool up ( const Key& key );
        static bool down ( const Key& key );
        static bool toggled ( const Key& key );

        /* methods. */
    public:
        int identifier () const;
    };

} }

#endif /* _w32_gdi_Key_hpp__ */
