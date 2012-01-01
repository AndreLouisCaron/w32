#ifndef _w32_fs_unlink_hpp__
#define _w32_fs_unlink_hpp__

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
     * @brief Remove a name for a file or folder, deleting it if necessary.
     */
    void unlink ( const string& path );

} }

#endif /* _w32_fs_unlink_hpp__ */
