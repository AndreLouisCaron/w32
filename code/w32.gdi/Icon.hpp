#ifndef _w32_gdi_Icon_hpp__
#define _w32_gdi_Icon_hpp__

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
#include <w32/Resource.hpp>
#include <w32/NotCopyable.hpp>
#include <w32.gdi/Size.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Pictogram for an action, state or tool, etc.
         */
    class Icon
    {
        /* nested types. */
    public:
        typedef Reference< ::HICON, void(*)(::HICON) > Handle;

        class Size;

        /* class methods. */
    public:
        static Handle claim ( ::HICON object );
        static Handle proxy ( ::HICON object );

        /* class data. */
    public:
        static const Icon none ();
        static const Icon application ();
        static const Icon asterisk ();
        static const Icon error ();
        static const Icon exclamation ();
        static const Icon hand ();
        static const Icon information ();
        static const Icon question ();
        static const Icon warning ();
        static const Icon winlogo ();

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Icon ( const Handle& handle );
        explicit Icon ( const string& path );
        explicit Icon ( const Resource& resource );
        Icon ( const Resource& resource, const Size& size );
        Icon ( const Resource& resource, const w32::gdi::Size& size );

        /* methods. */
    public:
            /*!
             * @brief Obtains the icon's handle.
             */
        const Handle& handle () const;
    };

    class Icon::Size
    {
        /* nested types. */
    public:
        typedef w32::gdi::Size Value;

        /* class data. */
    public:
        static const Size big ();
        static const Size small ();

        /* data. */
    private:
        Value mySize;

        /* construction. */
    private:
        explicit Size ( const Value& size );

        /* methods. */
    public:
        const Value& value () const;
    };

} }

#endif /* _win32gdi_Icon_hpp__ */
