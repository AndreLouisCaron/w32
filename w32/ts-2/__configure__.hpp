#ifndef _w32_ts2_configure_hpp__
#define _w32_ts2_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#ifdef __building_w32_ts2__
#   define W32_TS2_EXPORT __declspec(dllexport)
#   include "../__compiler-intro__.hpp"
#   ifdef _MSC_VER
#       pragma comment ( lib, "taskschd.lib" )
#   endif
#else
#   define W32_TS2_EXPORT __declspec(dllimport)
#endif

#include <taskschd.h>

#include <w32/bstring.hpp>
#include <w32/types.hpp>

    // Yet another COM-based Windows API!
#include <w32.com.hpp>

#endif /* _w32_ts_2_configure_hpp__ */
