#ifndef _w32_cr_Hash_hpp__
#define _w32_cr_Hash_hpp__

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
 * @file w32.cr/Hash.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32/types.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace cr {

    class Blob;
    class Key;
    class Provider;

    //! @addtogroup w32-cr
    //! @{

    class Hash
    {
        /* nested types. */
    public:
        typedef Reference< ::HCRYPTHASH > Handle;

        class Type;

        /* class methods. */
    public:
        static const Handle claim ( ::HCRYPTHASH object );
        static const Handle proxy ( ::HCRYPTHASH object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Hash ( const Provider& provider, const Type& type );

        /* methods. */
    public:
        const Handle& handle () const;

        void put ( const void * data, dword size );
        void put ( const Key& key );

        const Type type () const;
        dword size () const;
        Blob data () const;
        bool verify ( const Key& key, const Blob& signature );
    };

    class Hash::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static const Type md2 ();
        static const Type md4 ();
        static const Type md5 ();
        static const Type rc2 ();
        static const Type sha1 ();
        static const Type sha256 ();
        static const Type sha384 ();
        static const Type sha512 ();

        static const Type of ( const Hash& hash );

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

    Hash md5 ( const Provider& provider, const void * data, dword size );
    Hash sha1 ( const Provider& provider, const void * data, dword size );

    //! @}

} }

#endif /* _w32_cr_Hash_hpp__ */
