#ifndef _w32_msi_configure_hpp__
#define _w32_msi_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../w32/__configure__.hpp"

#define _WIN32_MSI 0x300
#include <Windows.h>
#include <Msi.h>
#include <MsiDefs.h>
#include <MsiQuery.h>

#include "../w32/__compiler-intro__.hpp"
#   include <w32/string.hpp>
#   include <w32/types.hpp>
#include "../w32/__compiler-outro__.hpp"

#ifdef _MSC_VER
#   pragma comment ( lib, "Msi.lib" )
#endif

#endif /* _w32_msi_configure_hpp__ */
