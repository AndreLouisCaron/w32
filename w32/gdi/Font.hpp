#ifndef _w32_gdi_Font_hpp__
#define _w32_gdi_Font_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/string.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Text-rendering utility.
         */
    class W32_GDI_EXPORT Font
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

    class W32_GDI_EXPORT Font::Attributes
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
