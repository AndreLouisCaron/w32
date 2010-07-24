#ifndef _w32_xml_dom_Node_hpp__
#define _w32_xml_dom_Node_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class Attributes;
    class Document;
    class Element;

        /*!
         * @brief XML Document tree node.
         */
    class W32_XML_DOM_EXPORT Node
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMNode > Ptr;

        class Type;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        Node ( const Ptr& ptr );

            /*!
             * @brief Extracts the root node from a Document.
             */
        Node ( const Document& document );

            /*!
             * @brief Extracts the root node from a Document.
             */
        Node ( const Element& element );

        /* methods. */
    public:
        Ptr get () const;
        void append ( const Node& node );
        Node parent () const;
        Node first () const;
        Node last () const;
        Node next () const;
        Node previous () const;
        Document owner () const;
        Attributes attributes () const;
        string tag () const;
        string text () const;
        void text ( const string& text );
        Type type () const;
    };

        /*!
         * @brief Enumeration of node types.
         */
    class W32_XML_DOM_EXPORT Node::Type
    {
        /* nested types. */
    public:
        typedef ::DOMNodeType Value;

        /* class data. */
    public:
        static const Type element ();
        static const Type attribute ();
        static const Type text ();
        static const Type cdata ();
        static const Type entityref ();
        static const Type entity ();
        static const Type instruction ();
        static const Type comment ();
        static const Type document ();
        static const Type document_type ();
        static const Type fragment ();
        static const Type notation ();

        /* data. */
    private:
        Value myValue;

        /* class methods. */
    public:
        static Type of ( const Node& node );

        /* construction. */
    private:
            // For internal use only.
        Type ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const Type& rhs ) const;
        bool operator!= ( const Type& rhs ) const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMNode > ()
{
    return (IID_IXMLDOMNode);
}

#endif /* _w32_xml_dom_Node_hpp__ */
