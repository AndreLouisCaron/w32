#ifndef _w32_in_Check_hpp__
#define _w32_in_Check_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>

namespace w32 { namespace in {

    /*!
     * @ingroup w32-in
     * @brief
     */
    void check ( bool force=false );

    /*!
     * @ingroup w32-in
     * @brief
     */
    void check ( const string& url, bool force=false );

} }

#endif /* _w32_in_Check_hpp__ */
