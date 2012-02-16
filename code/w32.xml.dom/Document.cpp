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
