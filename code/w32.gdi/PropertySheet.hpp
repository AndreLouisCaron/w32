#ifndef _w32_gdi_PropertySheet_hpp__
#define _w32_gdi_PropertySheet_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Resource.hpp>
#include <w32/Error.hpp>
#include <w32.gdi/Control.hpp>
#include <w32.gdi/Dialog.hpp>

namespace w32 { namespace gdi {

    class PropertySheet :
        virtual public Control
    {
        /* nested types. */
    public:
        class PageInfo;
        class Page;
        class PageAdder;

        /* methods. */
    public:
    };

    class PropertySheet::PageInfo :
        private w32::NotCopyable
    {
        /* data. */
    protected:
        ::PROPSHEETPAGEW myData;

        /* construction. */
    protected:
        PageInfo ();

        /* methods. */
    public:
        const ::PROPSHEETPAGEW& get () const;

        void title ( const wchar_t * value );

        void callback ( ::LPFNPSPCALLBACKW function );

        void template_ ( const Resource& template_ );

        void template_ ( const Dialog::Template& template_ );

        void icon ( const w32::gdi::Icon& image );

        void dialog ( ::DLGPROC procedure );

        void parameter ( void * pointer );
    };

    class PropertySheet::Page :
        private w32::NotCopyable
    {
        /* data. */
    private:
        ::HPROPSHEETPAGE myHandle;

        /* construction. */
    public:
        Page ( const PageInfo& info );

        ~Page ();

        /* methods. */
    public:
        ::HPROPSHEETPAGE handle () const;
    };

        /*!
         * @brief Simplifies the use of page-adding callbacks.
         */
    class PropertySheet::PageAdder
    {
        /* data. */
    private:
        ::LPFNADDPROPSHEETPAGE myFunction;
        ::LPARAM myParameter;

        /* construction. */
    public:
        PageAdder ( ::LPFNADDPROPSHEETPAGE function, ::LPARAM parameter );

        /* operators. */
    public:
        void operator() ( const Page& page );

        void operator() ( const PageInfo& info );
    };

} }

#endif /* _w32c_gdi_PropertySheet_hpp__ */
