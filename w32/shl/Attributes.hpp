#ifndef _w32_shl_Attributes_hpp__
#define _w32_shl_Attributes_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace shl {

    class Item;

    class Attributes
    {
        /* nested types. */
    public:
        typedef ::SFGAOF Value;

        /* class methods. */
    public:
        static const Attributes copyable ();
        static const Attributes moveable ();
        static const Attributes linkable ();
        static const Attributes storable ();
        static const Attributes renamable ();
        static const Attributes deletable ();
        static const Attributes haspropsheet ();
        static const Attributes droptarget ();
        static const Attributes encrypted ();
        static const Attributes slow ();
        static const Attributes ghosted ();
        static const Attributes link ();
        static const Attributes shared ();
        static const Attributes readonly ();
        static const Attributes hidden ();
        static const Attributes stream ();
        static const Attributes container ();
        static const Attributes removable ();
        static const Attributes compressed ();
        static const Attributes browsable ();
        static const Attributes folder ();
        static const Attributes filesystem ();
        static const Attributes subfolders ();

            // Use as masks.
        static const Attributes capabilities ();
        static const Attributes all ();

        static const Attributes of ( const Item& item, Attributes mask );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Attributes ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
        operator bool () const;

        Attributes& operator&= ( const Attributes& rhs );
        Attributes& operator|= ( const Attributes& rhs );
        Attributes operator& ( const Attributes& rhs ) const;
        Attributes operator| ( const Attributes& rhs ) const;
    };

} }

#endif /* _w32_shl_Attributes_hpp__ */
