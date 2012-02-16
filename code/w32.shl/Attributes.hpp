#ifndef _w32_shl_Attributes_hpp__
#define _w32_shl_Attributes_hpp__

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

namespace w32 { namespace shl {

    class Item;

    class Attributes
    {
        /* nested types. */
    public:
        typedef ::SFGAOF Value;

        /* class methods. */
    public:
        static const Attributes copyable ();
        static const Attributes moveable ();
        static const Attributes linkable ();
        static const Attributes storable ();
        static const Attributes renamable ();
        static const Attributes deletable ();
        static const Attributes haspropsheet ();
        static const Attributes droptarget ();
        static const Attributes encrypted ();
        static const Attributes slow ();
        static const Attributes ghosted ();
        static const Attributes link ();
        static const Attributes shared ();
        static const Attributes readonly ();
        static const Attributes hidden ();
        static const Attributes stream ();
        static const Attributes container ();
        static const Attributes removable ();
        static const Attributes compressed ();
        static const Attributes browsable ();
        static const Attributes folder ();
        static const Attributes filesystem ();
        static const Attributes subfolders ();

            // Use as masks.
        static const Attributes capabilities ();
        static const Attributes all ();

        static const Attributes of ( const Item& item, Attributes mask );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Attributes ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
        operator bool () const;

        Attributes& operator&= ( const Attributes& rhs );
        Attributes& operator|= ( const Attributes& rhs );
        Attributes operator& ( const Attributes& rhs ) const;
        Attributes operator| ( const Attributes& rhs ) const;
    };

} }

#endif /* _w32_shl_Attributes_hpp__ */
