// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#ifndef _w32_compiler_hpp__
#   define _w32_compiler_hpp__
#   ifdef _MSC_VER
#       pragma warning ( push )
#       pragma warning ( disable : 4251 )
#       pragma warning ( disable : 4250 )
#       pragma warning ( disable : 4996 )
#       pragma push_macro("_SCL_SECURE_NO_WARNINGS")
#       ifndef _SCL_SECURE_NO_WARNINGS
#           define _SCL_SECURE_NO_WARNINGS
#       endif
#       pragma push_macro("_CRT_SECURE_NO_WARNINGS")
#       ifndef _CRT_SECURE_NO_WARNINGS
#           define _CRT_SECURE_NO_WARNINGS
#       endif
#   endif
#else
#   undef _w32_compiler_hpp__
#   ifdef _MSC_VER
#       pragma pop_macro("_SCL_SECURE_NO_WARNINGS")
#       pragma pop_macro("_CRT_SECURE_NO_WARNINGS")
#       pragma warning ( pop )
#   endif
#endif /* _w32_compiler_hpp__ */
