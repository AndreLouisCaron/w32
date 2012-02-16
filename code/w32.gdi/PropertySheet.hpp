#ifndef _w32_gdi_PropertySheet_hpp__
#define _w32_gdi_PropertySheet_hpp__

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
