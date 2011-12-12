#ifndef _w32_xml_dom_configure_hpp__
#define _w32_xml_dom_configure_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../w32/__configure__.hpp"

#include <msxml6.h>

#include <w32/bstring.hpp>
#include <w32.com/cast.hpp>
#include <w32.com/Error.hpp>
#include <w32.com/Guid.hpp>
#include <w32.com/Ptr.hpp>
#include <w32.com/Result.hpp>

namespace w32 { namespace xml { namespace dom {

    typedef w32::bstring string;

} } }

#endif /* _w32_xml_dom_configure_hpp__ */
