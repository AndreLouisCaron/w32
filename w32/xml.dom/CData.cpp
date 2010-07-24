// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/xml.dom/CData.hpp>

namespace w32 { namespace xml { namespace dom {

    CData::CData ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    CData::Ptr CData::get () const
    {
        return (myPtr);
    }

} } }
