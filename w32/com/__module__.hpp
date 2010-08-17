#ifndef _w32_com_hpp__
#define _w32_com_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32{
    namespace com {}
}


#include "../__compiler-intro__.hpp"
#   include <w32/com/Allocator.hpp>
#   include <w32/com/cast.hpp>
#   include <w32/com/Error.hpp>
#   include <w32/com/Factory.hpp>
#   include <w32/com/Guid.hpp>
#   include <w32/com/instantiate.hpp>
#   include <w32/com/Library.hpp>
#   include <w32/com/Model.hpp>
#   include <w32/com/Object.hpp>
#   include <w32/com/Ptr.hpp>
#   include <w32/com/Result.hpp>
#include "../__compiler-outro__.hpp"

#endif /* _com_hpp__ */
