#ifndef _w32_shl_ext_configure_hpp__
#define _w32_shl_ext_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#include <ObjIdl.h>
#include <ShlObj.h>
#include <Shtypes.h>
#include <ThumbCache.h>
#include <PropSys.h>

    // This is directly embedded in the UI.
#include <w32.hpp>
#include <w32.com.hpp>
#include <w32.fs.hpp>
#include <w32.gdi.hpp>


    // Remove nasty <Windows.h> macros that conflict with our names.
#if (defined(PropertySheet))
#   undef PropertySheet
#endif

#endif /* _w32_shl_ext_configure_hpp__ */
