#ifndef _w32_cr_Blob_hpp__
#define _w32_cr_Blob_hpp__

// Copyright(c) Andre Caron, 2009-2012
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
