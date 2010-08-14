#ifndef _w32_sc_configure_hpp__
#define _w32_sc_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#ifdef __building_w32_sc__
#   define W32_SC_EXPORT __declspec(dllexport)
#   include "../__compiler-intro__.hpp"
#else
#   define W32_SC_EXPORT __declspec(dllimport)
#endif

#endif /* _w32_configure_hpp__ */
