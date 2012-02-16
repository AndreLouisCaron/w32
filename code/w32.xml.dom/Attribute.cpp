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

#include <w32.xml.dom/Attribute.hpp>
#include <w32.xml.dom/Node.hpp>
#include <w32/Variant.hpp>

namespace w32 { namespace xml { namespace dom {

    Attribute::Attribute ( const Ptr& ptr )
        : myPtr(ptr)
    {
    }

    Attribute::Attribute ( const Node& node )
        : myPtr(com::cast< ::IXMLDOMAttribute >(node.get()))
    {
    }

    Attribute::Ptr Attribute::get () const
    {
        return (myPtr);
    }

    string Attribute::name () const
    {
            // Obtain the argument value, whatever it is.
        ::BSTR name;
        const com::Result result = myPtr->get_name(&name);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMAttribute, get_name, result);
        }
        
        return (string(string::box(name)));
    }

    string Attribute::value () const
    {
            // Obtain the argument value, whatever it is.
        Variant variant;
        const com::Result result = myPtr->get_value(&variant.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMAttribute, get_value, result);
        }
        
            // Use normal variant coercion rules.
        return (variant);
    }

    void Attribute::value ( const string& value )
    {
        Variant variant; variant = value;
        const com::Result result = myPtr->put_value(variant.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IXMLDOMAttribute, put_value, result);
        }
    }

} } }
