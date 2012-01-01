#ifndef _w32_fs_hardlink_hpp__
#define _w32_fs_hardlink_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>

namespace w32 { namespace fs {

    /*!
     * @ingroup w32-fs
     * @brief Create a new name for an existing file.
     * @see junction()
     */
    void hardlink ( const string& alias, const string& target );

} }

#endif /* _w32_fs_hardlink_hpp__ */
