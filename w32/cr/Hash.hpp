#ifndef _w32_cr_Hash_hpp__
#define _w32_cr_Hash_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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

    class W32_CR_EXPORT Hash
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

    class W32_CR_EXPORT Hash::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static const Type md5 ();
        static const Type rc2 ();

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

} }

#endif /* _w32_cr_Hash_hpp__ */
