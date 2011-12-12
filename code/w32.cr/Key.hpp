#ifndef _w32_cr_Key_hpp__
#define _w32_cr_Key_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>
#include <w32.cr/Hash.hpp>

namespace w32 { namespace cr {

    class Hash;
    class Provider;

    class Key
    {
        /* nested types. */
    public:
        typedef Reference< ::HCRYPTKEY > Handle;

        class Type;

        /* class methods. */
    public:
        static const Handle claim ( ::HCRYPTKEY object );
        static const Handle proxy ( ::HCRYPTKEY object );

        static Key generate ( const Provider& provider, const Type& type );
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

} }

#endif /* _w32_cr_Key_hpp__ */
