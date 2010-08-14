#ifndef _w32_configure_hpp__
#define _w32_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#ifdef __building_w32_core__
#   define W32_CORE_EXPORT __declspec(dllexport)
#   include "__compiler-intro__.hpp"
#else
#   define W32_CORE_EXPORT __declspec(dllimport)
#endif

    // Define preferred windows version.
#if (!defined(_WIN32_WINNT))
#   define _WIN32_WINNT 0x0600
#endif

    // API headers.
#ifndef _WINDOWS_
#   include <Windows.h>
#endif
#ifndef __oleidl_h__
#   include <OLEIdl.h>
#endif
    // Structured exception handling.
#ifndef _INC_EH
#   include <eh.h>
#endif

    // Remove conflicting macros.
#if (defined(big))
#   undef big
#endif
#if (defined(small))
#   undef small
#endif
#if (defined(min))
#   undef min
#endif
#if (defined(max))
#   undef max
#endif

#endif /* _w32_configure_hpp__ */
