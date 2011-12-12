// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.xml.dom/Document.hpp>
#include <w32.xml.dom/Element.hpp>
#include <w32.xml.dom/Error.hpp>
#include <w32.xml.dom/List.hpp>
#include <w32.xml.dom/Node.hpp>
#include <w32/Variant.hpp>

namespace {

    w32::com::Ptr< ::IXMLDOMDocument2 > create ()
    {
        ::IXMLDOMDocument2 * document = 0;
        const w32::com::Result result = ::CoCreateInstance(
            __uuidof(::DOMDocument60), 0, CLSCTX_ALL,
            __uuidof(::IXMLDOMDocument2), (void**)&document
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument2, CoCreateInstance, result);
        }
        return (w32::com::Ptr< ::IXMLDOMDocument2 >(document));
    }

}

namespace w32 { namespace xml { namespace dom {

    Document::Document ()
        : myPtr(::create())
    {
    }

    Document::Document ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    Document::Ptr Document::get () const
    {
        return (myPtr);
    }

    void Document::preserveWhiteSpace ( bool enable )
    {
        const ::VARIANT_BOOL status = (enable)? VARIANT_TRUE : VARIANT_FALSE;
        const com::Result result = myPtr->put_preserveWhiteSpace(status);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, put_preserveWhitespace, result);
        }
    }

    void Document::validateOnParse ( bool enable )
    {
        const ::VARIANT_BOOL status = (enable)? VARIANT_TRUE : VARIANT_FALSE;
        const com::Result result = myPtr->put_validateOnParse(status);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, put_validateOnParse, result);
        }
    }

    void Document::property_ ( const string& name, bool enable )
    {
        w32::Variant status; status = enable;
        const com::Result result = myPtr->setProperty(name.value(), status.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, setProperty, result);
        }
    }

    void Document::prohibitDTD ( bool enable )
    {
        property_(L"ProhibitDTD", enable);
    }

    void Document::resolveExternals ( bool enable )
    {
        property_(L"ResolveExternals", enable);
    }

    bool Document::open ( const string& url )
    {
        ::VARIANT_BOOL status = VARIANT_FALSE;
        w32::Variant source; source = url;
        const com::Result result = myPtr->load(source.value(), &status);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, load, result);
        }
        return (status == VARIANT_TRUE);
    }

    bool Document::load ( const string& content )
    {
        ::VARIANT_BOOL status = VARIANT_FALSE;
        const com::Result result = myPtr->loadXML(content.value(), &status);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, loadXML, result);
        }
        return (status == VARIANT_TRUE);
    }

    Error Document::validate () const
    {
        ::IXMLDOMParseError * error = 0;
        const com::Result result = myPtr->validate(&error);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, validate, result);
        }
        return (Error::Ptr(error));
    }

    Element Document::element ( const string& tag )
    {
        ::IXMLDOMElement * element = 0;
        const com::Result result = myPtr->createElement(tag.value(), &element);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, createElement, result);
        }
        return (Element::Ptr(element));
    }

    Node Document::match ( const string& query ) const
    {
        ::IXMLDOMNode * node = 0;
        const com::Result result = myPtr->selectSingleNode(query.value(), &node);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, selectNodes, result);
        }
        return (Node::Ptr(node));
    }

    List Document::matches ( const string& query ) const
    {
        ::IXMLDOMNodeList * list = 0;
        const com::Result result = myPtr->selectNodes(query.value(), &list);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMDocument, selectNodes, result);
        }
        return (List::Ptr(list));
    }

} } }
