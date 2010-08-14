#ifndef _w32_gdi_configure_hpp__
#define _w32_gdi_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../__configure__.hpp"

#ifdef __building_w32_gdi__
#   define W32_GDI_EXPORT __declspec(dllexport)
#   include "../__compiler-intro__.hpp"
#   ifdef _MSC_VER
#       pragma comment ( lib, "ComCtl32.lib" )
#       pragma comment ( lib, "OpenGL32.lib" )
#   endif
#else
#   define W32_GDI_EXPORT __declspec(dllimport)
#endif

    // API headers.
#ifndef _INC_WINDOWSX
#   include <WindowsX.h>
#endif
#ifndef _INC_COMMCTRL
#   include <CommCtrl.h>
#endif
#ifndef _PRSHT_H_
#   include <PrSht.h>
#endif

    // Remove conflicting macros.
#if (defined(PropertySheet))
#   undef PropertySheet
#endif

#endif /* _w32_gdi_configure_hpp__ */
