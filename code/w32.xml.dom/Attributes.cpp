// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.xml.dom/Attributes.hpp>
#include <w32.xml.dom/Node.hpp>

namespace w32 { namespace xml { namespace dom {

    Attributes::Attributes ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    Attributes::Ptr Attributes::get () const
    {
        return (myPtr);
    }

    Attributes::size_type Attributes::length () const
    {
        long length = 0;
        const com::Result result = myPtr->get_length(&length);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNamedNodeMap, get_length, result);
        }
        return (length);
    }

    Attributes::size_type Attributes::size () const
    {
        return (length());
    }

    void Attributes::reset ()
    {
        const com::Result result = myPtr->reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNamedNodeMap, reset, result);
        }
    }

    Node Attributes::operator() ( size_type i ) const
    {
        ::IXMLDOMNode * item = 0;
        const com::Result result = myPtr->get_item(i, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNamedNodeMap, get_item, result);
        }
        return (Node::Ptr(item));
    }

    Node Attributes::operator() ( const string& name ) const
    {
        ::IXMLDOMNode * item = 0;
        const com::Result result = myPtr->getNamedItem(name.value(), &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNamedNodeMap, getNamedItem, result);
        }
        return (Node::Ptr(item));
    }

    void Attributes::operator() ( Node node )
    {
        ::IXMLDOMNode * item = 0;
        const com::Result result = myPtr->setNamedItem(node.get().value(), &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNamedNodeMap, setNamedItem, result);
        }
            // Release reference count to object.
        Node::Ptr _(item);
    }

} } }
