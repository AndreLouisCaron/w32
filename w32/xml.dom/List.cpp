// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/xml.dom/List.hpp>
#include <w32/xml.dom/Node.hpp>

namespace w32 { namespace xml { namespace dom {

    List::List ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    List::Ptr List::get () const
    {
        return (myPtr);
    }

    List::size_type List::length () const
    {
        long length = 0;
        const com::Result result = myPtr->get_length(&length);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNodeList, get_length, result);
        }
        return (length);
    }

    List::size_type List::size () const
    {
        return (length());
    }

    void List::reset ()
    {
        const com::Result result = myPtr->reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNodeList, reset, result);
        }
    }

    Node List::operator() ( size_type i ) const
    {
        ::IXMLDOMNode * item = 0;
        const com::Result result = myPtr->get_item(i, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNodeList, get_item, result);
        }
        return (Node::Ptr(item));
    }

} } }
