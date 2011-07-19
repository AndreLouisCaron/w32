#ifndef _w32_shl_Browser_hpp__
#define _w32_shl_Browser_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/shl/Path.hpp>

namespace w32 { namespace shl {

    class Browser
    {
        /* nested types. */
    public:
        typedef ::BROWSEINFOW Data;

        class Hints;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Browser ();
        Browser ( const Hints& hints );

        /* methods. */
    public:
        void title ( const string& text );
        Path prompt ();
    };

    class Browser::Hints
    {
        /* nested types. */
    public:
        typedef ::UINT Value;

        /* class data. */
    public:
        static const Hints folders ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Hints ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;

        Hints& operator|= ( const Hints& rhs );
        Hints operator| ( const Hints& rhs );
    };

} }

#endif /* _w32_shl_Browser_hpp__ */
