#ifndef _w32_xml_dom_Attribute_hpp__
#define _w32_xml_dom_Attribute_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class Node;

    class W32_XML_DOM_EXPORT Attribute
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMAttribute > Ptr;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        Attribute ( const Ptr& ptr );
        explicit Attribute ( const Node& node );

        /* methods. */
    public:
        Ptr get () const;

            /*!
             * @brief Obtains the attribute's name.
             */
        string name () const;

            /*!
             * @brief Obtains the attribute's value.
             */
        string value () const;

            /*!
             * @brief Sets the attribute's value.
             */
        void value ( const string& value );
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMAttribute > ()
{
    return (IID_IXMLDOMAttribute);
}

#endif /* _w32_xml_dom_Attribute_hpp__ */
