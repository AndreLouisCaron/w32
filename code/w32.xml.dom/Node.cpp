// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.xml.dom/Node.hpp>
#include <w32.xml.dom/Attributes.hpp>
#include <w32.xml.dom/Document.hpp>
#include <w32.xml.dom/Element.hpp>
#include <w32.xml.dom/List.hpp>
#include <w32/Variant.hpp>

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

    Node::operator bool () const
    {
        return (myPtr.ok());
    }

    bool Node::operator! () const
    {
        return (myPtr.bad());
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

    Node Node::match ( const string& query ) const
    {
        ::IXMLDOMNode * node = 0;
        const com::Result result = myPtr->selectSingleNode(query.value(), &node);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, selectNodes, result);
        }
        return (Node::Ptr(node));
    }

    List Node::matches ( const string& query ) const
    {
        ::IXMLDOMNodeList * list = 0;
        const com::Result result = myPtr->selectNodes(query.value(), &list);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, selectNodes, result);
        }
        return (List::Ptr(list));
    }

    string Node::value () const
    {
        Variant value;
        const com::Result result = myPtr->get_nodeValue(&value.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, get_nodeValue, result);
        }
        return (value);
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
