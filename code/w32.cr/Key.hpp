#ifndef _w32_cr_Key_hpp__
#define _w32_cr_Key_hpp__

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

/*!
 * @file w32.cr/Key.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32.cr/Hash.hpp>

namespace w32 { namespace cr {

    class Hash;
    class Provider;

    //! @addtogroup w32-cr
    //! @{

    class Key
    {
        /* nested types. */
    public:
        typedef Reference< ::HCRYPTKEY > Handle;

        class Type;
        class Hints;

        /* class methods. */
    public:
        static const Handle claim ( ::HCRYPTKEY object );
        static const Handle proxy ( ::HCRYPTKEY object );

        static Key generate ( const Provider& provider, const Type& type );
        static Key generate ( const Provider& provider,
                              const Type& type, const Hints& hints );
        static Key derive ( const Provider& provider,
            const Hash& hash, const Hash::Type& algorithm );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Key ( const Handle& handle );
        Key ( const Provider& provider, const Type& type );

        /* methods. */
    public:
        const Handle& handle () const;
    };

    class Key::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static Type exchange ();
        static Type signature ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* operators. */
    public:
        operator Value () const;
    };

    class Key::Hints
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Hints ();

        /* methods. */
    public:
        Hints& exportable ();

        /* operators. */
    public:
        operator Value () const;
    };

    //! @}

} }

#endif /* _w32_cr_Key_hpp__ */
