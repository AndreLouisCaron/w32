#ifndef _w32_com_Context_hpp__
#define _w32_com_Context_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace com {

    class W32_COM_EXPORT Context
    {
        /* nested types. */
    public:
        typedef ::CLSCTX Value;

        /* class data. */
    public:
        static const Context inprocess ();
        static const Context local ();
        static const Context remote ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Context ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

} }

#endif /* _w32_com_Context_hpp__ */
