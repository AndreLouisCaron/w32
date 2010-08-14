#ifndef _w32_shl_Item_hpp__
#define _w32_shl_Item_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/com/Wrapper.hpp>
#include <w32/shl/Path.hpp>

namespace w32 { namespace shl {

    class W32_SHL_EXPORT Item :
        public com::Wrapper< ::IShellItem >
    {
        /* construction. */
    public:
        explicit Item ( ::IShellItem * object );
        Item ( const Path& path );

        /* methods. */
    public:
        Item parent () const;
        string name () const;
    };

} }

#endif /* _w32_shl_Item_hpp__ */
