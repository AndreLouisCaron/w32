#ifndef _w32_shl_configure_hpp__
#define _w32_shl_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#ifdef __building_w32_shl__
#   define W32_SHL_EXPORT __declspec(dllexport)
#   include "../__compiler__.hpp"
#else
#   define W32_SHL_EXPORT __declspec(dllimport)
#endif

#include <ObjIdl.h>
#include <ShlObj.h>
#include <Shtypes.h>
#include <w32.com.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace shl {

    typedef w32::string string;

} }

#endif /* _w32_shl_configure_hpp__ */
