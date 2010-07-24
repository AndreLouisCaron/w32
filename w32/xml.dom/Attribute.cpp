// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/xml.dom/Attribute.hpp>
#include <w32/xml.dom/Node.hpp>
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
