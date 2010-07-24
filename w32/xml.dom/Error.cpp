// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/xml.dom/Error.hpp>

namespace w32 { namespace xml { namespace dom {

    Error::Error ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    Error::Ptr Error::get () const
    {
        return (myPtr);
    }

    string Error::reason () const
    {
        ::BSTR reason = 0;
        const com::Result result = myPtr->get_reason(&reason);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMParseError, get_reason, result);
        }
        return ((reason == 0)? string() : string(string::box(reason)));
    }

} } }
