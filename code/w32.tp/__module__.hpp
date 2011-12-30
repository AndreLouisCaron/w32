#ifndef _w32_tp_hpp__
#define _w32_tp_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 {
    namespace tp {}
}


#if (_WIN32_WINNT >= 0x600)
#  include <w32.tp/Cleanup.hpp>
#  include <w32.tp/Hints.hpp>
#  include <w32.tp/Timer.hpp>
#  include <w32.tp/Transfer.hpp>
#  include <w32.tp/Wait.hpp>
#  include <w32.tp/Work.hpp>
#  include <w32.tp/Pool.hpp>
#  include <w32.tp/Queue.hpp>
#endif

#endif /* _w32_tp_hpp__ */
