// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.xml.sax/Locator.hpp>

namespace w32 { namespace xml { namespace sax {

    Locator::Locator ( const Ptr& backend )
        : myBackend(backend)
    {
    }

    int Locator::line () const
    {
        int line = 0;
        const com::Result result = myBackend->getLineNumber(&line);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLLocator, getLineNumber, result);
        }
        return (line);
    }

    int Locator::column () const
    {
        int column = 0;
        const com::Result result = myBackend->getColumnNumber(&column);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLLocator, getColumnNumber, result);
        }
        return (column);
    }

} } }
