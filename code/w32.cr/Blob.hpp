#ifndef _w32_cr_Blob_hpp__
#define _w32_cr_Blob_hpp__

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
 * @file w32.cr/Blob.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace cr {

    class Provider;

    //! @addtogroup w32-cr
    //! @{

    class Blob
    {
        /* data. */
    public:
        dword mySize;
        byte* myData;

        /* construction. */
    public:
        Blob ( dword size );
        Blob ( dword size, const void * data );
        Blob ( const Blob& rhs );

        /* methods. */
    public:
        dword size () const;
        byte * data ();
        const byte * data () const;
        void swap ( Blob& rhs );
        void truncate ( dword size );

        /* operators. */
    public:
        Blob& operator= ( const Blob& rhs );
    };

        // For argument-dependent lookup.
    inline void swap ( Blob& lhs, Blob& rhs )
    {
        lhs.swap(rhs);
    }

    class Format
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static const Format hex ();
        static const Format hexraw ();
        static const Format hexascii ();
        static const Format base64 ();
        static const Format base64certificate ();
        static const Format base64request ();
        static const Format base64x509 ();
#if _WIN32_WINNT > 0x0600
        static const Format asn1 ();
#endif

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Format ( Value value );

        /* operators. */
    public:
        operator Value () const;
    };

    string convert
        ( const Blob& rhs, const Format& format=Format::hexraw() );
    Blob convert
        ( const string& rhs, const Format& format=Format::hexraw() );

    void random
        ( const Provider& provider, void * data, dword size );

    inline void random ( const Provider& provider, Blob& blob )
    {
        random(provider, blob.data(), blob.size());
    }

    inline Blob random ( const Provider& provider, dword size )
    {
        Blob blob(size); random(provider, blob); return (blob);
    }

    template<typename Number>
    inline Number random ( const Provider& provider )
    {
        Number number;
        random(provider, &number, sizeof(number));
        return (number);
    }

    //! @}

} }

#endif /* _w32_cr_Blob_hpp__ */
