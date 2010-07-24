#ifndef _w32_Object_hpp__
#define _w32_Object_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>

namespace w32 {

    class W32_CORE_EXPORT Object
    {
        /* nested types. */
    public:
        typedef Reference< ::HANDLE > Handle;

        static Handle claim ( ::HANDLE object );
        static Handle proxy ( ::HANDLE object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    protected:
        explicit Object ( const Handle& handle );
        Object ();

    public:
        virtual ~Object ();

        /* methods. */
    public:
        const Handle& handle () const;

        void destroy ();
    };

}

#endif /* _w32_Object_hpp__ */
