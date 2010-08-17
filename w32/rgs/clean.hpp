#ifndef _w32_rgs_clean_hpp__
#define _w32_rgs_clean_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/rgs/Key.hpp>

namespace w32 { namespace rgs {

    void W32_RGS_EXPORT clean ( Key& root );
    void W32_RGS_EXPORT clean ( Key& root, const string& path );

} }

#endif /* _w32_rgs_clean_hpp__ */
