#ifndef _w32_gdi_Font_hpp__
#define _w32_gdi_Font_hpp__

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

namespace w32 { namespace gdi {

        /*!
         * @brief Text-rendering utility.
         */
    class Font
    {
        /* nested types. */
    public:
        typedef Reference< ::HFONT, void(*)(::HFONT) > Handle;

        class Attributes;

        /* class methods. */
    public:
        static Handle claim ( ::HFONT object );
        static Handle proxy ( ::HFONT object );

        /* class data. */
    public:
            /*!
             * @brief Only font @e guaranteed to be available.
             */
        static const Font system ();

            /*!
             * @brief Fixed-width font.
             */
        static const Font monospace ();

            /*!
             * @brief Variable-width font.
             */
        static const Font proportional ();

            /*!
             * @brief Device resident font (super fast for printers).
             */
        static const Font device ();

            /*!
             * @brief For use with IBM PCs (legacy?).
             */
        static const Font oem ();

            /*!
             * @brief Obtains the font used to write icon titles.
             */
        static const Font iconTitle ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Font ( const Handle& handle );
        explicit Font ( const Attributes& attributes );

        /* methods. */
    public:
        const Handle& handle () const;

        void apply ( const Attributes& attributes );
    };

    class Font::Attributes
    {
        /* nested types. */
    public:
        typedef ::LOGFONTW Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Attributes ();
        Attributes ( const Font& font );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        string face () const;
        void face ( const string& face );
        long height () const;
        void height ( long height );
        long width () const;
        void width ( long width );
        long weight () const;
        void weight ( long height );
    };

} }

#endif /* _w32_gdi_Font_hpp__ */
