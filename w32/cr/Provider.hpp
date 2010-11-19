#ifndef _w32_cr_Provider_hpp__
#define _w32_cr_Provider_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace cr {

    class W32_CR_EXPORT Provider
    {
        /* nested types. */
    public:
        typedef Reference< ::HCRYPTPROV > Handle;

        class Type;

        /* class methods. */
    public:
        static const Handle claim ( ::HCRYPTPROV object );
        static const Handle proxy ( ::HCRYPTPROV object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Provider ( const Type& type );

        /* methods. */
    public:
        const Handle& handle () const;

        string name () const;
        string container () const;
    };

    class W32_CR_EXPORT Provider::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class methods. */
    public:
        static const Type rsafull ();
        static const Type rsaaes ();
        static const Type rsasig ();
        static const Type rsaschannel ();
        static const Type dss ();
        static const Type dssdh ();
        static const Type dhschannel ();
        static const Type fortezza ();
        static const Type msexchange ();
        static const Type ssl ();

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

#endif /* _w32_cr_Provider_hpp__ */
