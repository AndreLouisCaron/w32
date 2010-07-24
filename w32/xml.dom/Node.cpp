// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/xml.dom/Node.hpp>
#include <w32/xml.dom/Attributes.hpp>
#include <w32/xml.dom/Document.hpp>
#include <w32/xml.dom/Element.hpp>

namespace w32 { namespace xml { namespace dom {

    Node::Node ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    Node::Node ( const Document& document )
        : myPtr(com::cast< ::IXMLDOMNode >(document.get()))
    {
    }

    Node::Node ( const Element& element )
        : myPtr(com::cast< ::IXMLDOMNode >(element.get()))
    {
    }

    Node::Ptr Node::get () const
    {
        return (myPtr);
    }

    void Node::append ( const Node& node )
    {
        ::IXMLDOMNode * child = 0;
        const com::Result result = myPtr->appendChild(
            node.get().value(), &child
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, appendChild, result);
        }
    }

    Node Node::parent () const
    {
        ::IXMLDOMNode * parent = 0;
        const com::Result result = myPtr->get_parentNode(&parent);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_parentNode, result);
        }
        return (Node::Ptr(parent));
    }

    Node Node::first () const
    {
        ::IXMLDOMNode * child = 0;
        const com::Result result = myPtr->get_firstChild(&child);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_firstChild, result);
        }
        return (Node::Ptr(child));
    }

    Node Node::last () const
    {
        ::IXMLDOMNode * child = 0;
        const com::Result result = myPtr->get_lastChild(&child);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_lastChild, result);
        }
        return (Node::Ptr(child));
    }

    Node Node::next () const
    {
        ::IXMLDOMNode * sibling = 0;
        const com::Result result = myPtr->get_nextSibling(&sibling);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_nextSibling, result);
        }
        return (Node::Ptr(sibling));
    }

    Node Node::previous () const
    {
        ::IXMLDOMNode * sibling = 0;
        const com::Result result = myPtr->get_previousSibling(&sibling);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_previousSibling, result);
        }
        return (Node::Ptr(sibling));
    }

#if 0 // Can't use Document2 or Document30?
    Document Node::owner () const
    {
        ::IXMLDOMDocument * document = 0;
        const com::Result result = myPtr->get_ownerDocument(&document);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_ownerDocument, result);
        }
        return (Document::Ptr(document));
    }
#endif

    Attributes Node::attributes () const
    {
        ::IXMLDOMNamedNodeMap * attributes = 0;
        const com::Result result = myPtr->get_attributes(&attributes);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_attributes, result);
        }
        return (Attributes::Ptr(attributes));
    }

    string Node::tag () const
    {
        ::BSTR name = 0;
        const com::Result result = myPtr->get_nodeName(&name);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMParseError, get_nodeName, result);
        }
        return ((name == 0)? string() : string(string::box(name)));
    }

    string Node::text () const
    {
        ::BSTR text = 0;
        const com::Result result = myPtr->get_text(&text);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMParseError, get_text, result);
        }
        return ((text == 0)? string() : string(string::box(text)));
    }

    void Node::text ( const string& text )
    {
        const com::Result result = myPtr->put_text(text.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMParseError, put_text, result);
        }
    }

    Node::Type Node::type () const
    {
        return (Type::of(*this));
    }

    const Node::Type Node::Type::element ()
    {
        return (NODE_ELEMENT);
    }

    const Node::Type Node::Type::attribute ()
    {
        return (NODE_ATTRIBUTE);
    }

    const Node::Type Node::Type::text ()
    {
        return (NODE_TEXT);
    }

    const Node::Type Node::Type::cdata ()
    {
        return (NODE_CDATA_SECTION);
    }

    const Node::Type Node::Type::entityref ()
    {
        return (NODE_ENTITY_REFERENCE);
    }

    const Node::Type Node::Type::entity ()
    {
        return (NODE_ENTITY);
    }

    const Node::Type Node::Type::instruction ()
    {
        return (NODE_PROCESSING_INSTRUCTION);
    }

    const Node::Type Node::Type::comment ()
    {
        return (NODE_COMMENT);
    }

    const Node::Type Node::Type::document ()
    {
        return (NODE_DOCUMENT);
    }

    const Node::Type Node::Type::document_type ()
    {
        return (NODE_DOCUMENT_TYPE);
    }

    const Node::Type Node::Type::fragment ()
    {
        return (NODE_DOCUMENT_FRAGMENT);
    }

    const Node::Type Node::Type::notation ()
    {
        return (NODE_NOTATION);
    }

    Node::Type Node::Type::of ( const Node& node )
    {
        ::DOMNodeType type = NODE_ELEMENT;
        const com::Result result = node.get()->get_nodeType(&type);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMNode, get_nodeType, result);
        }
        return (type);
    }

    Node::Type::Type ( Value value )
        : myValue(value)
    {
    }

    Node::Type::Value Node::Type::value () const
    {
        return (myValue);
    }

    bool Node::Type::operator== ( const Type& rhs ) const
    {
        return (myValue == rhs.myValue);
    }

    bool Node::Type::operator!= ( const Type& rhs ) const
    {
        return (! ((*this) == rhs) );
    }

} } }
