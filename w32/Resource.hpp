#ifndef _w32_Resource_hpp__
#define _w32_Resource_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Module.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>

namespace w32 {

    class W32_CORE_EXPORT Resource
    {
        /* nested types. */
    public:
        typedef Reference< const wchar_t* > Identifier;

        /* data. */
    private:
        Module myModule;
        Identifier myIdentifier;

        /* construction. */
    public:
        Resource ( const Module& module, int number );
        Resource ( const Module& module, const string& name );

        /* methods. */
    public:
        const Module& module () const;
        const Identifier& identifier () const;
    };

}

#endif /* _w32_Resource_hpp__ */
