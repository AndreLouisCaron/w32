#ifndef _w32_sc_Object_hpp__
#define _w32_sc_Object_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Reference.hpp>

namespace w32 { namespace sc {

    class Object
    {
        /* nested types. */
    public:
        typedef Reference< ::SC_HANDLE > Handle;

        static Handle claim ( ::SC_HANDLE object );
        static Handle proxy ( ::SC_HANDLE object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Object ( const Handle& handle );
        virtual ~Object ();

        /* methods. */
    public:
        const Handle& handle () const;
    };

} }

#endif /* _w32_sc_Object_hpp__ */
