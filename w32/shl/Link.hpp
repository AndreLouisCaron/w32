#ifndef _w32_shl_Link_hpp__
#define _w32_shl_Link_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Wrapper.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace shl {

    class Path;

    class W32_SHL_EXPORT Link :
        public com::Wrapper< ::IShellLinkW >
    {
        /* construction. */
    public:
        explicit Link ( ::IShellLinkW * object );
        Link ();

    public:
        void target ( const Path& path );
        Path target () const;
        void arguments ( const string& value );
        string arguments () const;
        void description ( const string& value );
        string description () const;
        void icon ( const string& path, int index=0 );
        string icon ( int& index ) const;
    };

} }

#endif /* _w32_shl_Link_hpp__ */
