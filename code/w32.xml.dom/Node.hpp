#ifndef _w32_xml_dom_Node_hpp__
#define _w32_xml_dom_Node_hpp__

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

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class Attributes;
    class Document;
    class Element;
    class List;

        /*!
         * @brief XML Document tree node.
         */
    class Node
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
        operator bool () const;
        bool operator! () const;
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
        string value () const;
        Type type () const;
        Node match ( const string& query ) const;
        List matches ( const string& query ) const;
    };

        /*!
         * @brief Enumeration of node types.
         */
    class Node::Type
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
