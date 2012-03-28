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

    string Attributes::valueof ( const string& name ) const
    {
        const Node node = (*this)(name);
        if ( !node ) {
            return (string());
        }
        return (node.value());
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
