#ifndef _w32_xml_dom_Visitor_hpp__
#define _w32_xml_dom_Visitor_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.xml.dom/Attribute.hpp>
#include <w32.xml.dom/CData.hpp>
#include <w32.xml.dom/Comment.hpp>
#include <w32.xml.dom/Document.hpp>
#include <w32.xml.dom/Element.hpp>
#include <w32.xml.dom/Instruction.hpp>
#include <w32.xml.dom/Node.hpp>
#include <w32.xml.dom/Text.hpp>

namespace w32 { namespace xml { namespace dom {

        /*!
         * @brief Visitor dispatcher.
         */
    template<typename Handler>
    class Visitor
    {
        /* data. */
    private:
        Handler myHandler;

        /* construction. */
    public:
        Visitor ( Handler handler )
            : myHandler(handler)
        {}

        /* operators. */
    public:
            // Dispatcher.
        void operator() ( const Node& node ) const
        {
            if ( node.type() == Node::Type::text() )
            {
                const Text::Ptr text =
                    com::cast< ::IXMLDOMText >(node.get());
                myHandler(text);
            }
            else if ( node.type() == Node::Type::element() )
            {
                const Element::Ptr element =
                    com::cast< ::IXMLDOMElement >(node.get());
                myHandler(element);
            }
            else if ( node.type() == Node::Type::attribute() )
            {
                const Attribute::Ptr attribute =
                    com::cast< ::IXMLDOMAttribute >(node.get());
                myHandler(attribute);
            }
            else if ( node.type() == Node::Type::comment() )
            {
                const Comment::Ptr comment =
                    com::cast< ::IXMLDOMComment >(node.get());
                myHandler(comment);
            }
            else if ( node.type() == Node::Type::cdata() )
            {
                const CData::Ptr cdata =
                    com::cast< ::IXMLDOMCDATASection >(node.get());
                myHandler(cdata);
            }
            else if ( node.type() == Node::Type::instruction() )
            {
                const Instruction::Ptr instruction =
                    com::cast< ::IXMLDOMProcessingInstruction >(node.get());
                myHandler(instruction);
            }
            else if ( node.type() == Node::Type::document() )
            {
                const Document::Ptr document =
                    com::cast< ::IXMLDOMDocument2 >(node.get());
                myHandler(document);
            }
        }
    };

        // Factory function to deduce template argument.
    template<typename Handler>
    Visitor<Handler> make_visitor ( Handler handler )
    {
        return (Visitor<Handler>(handler));
    }

} } }

#endif /* _w32_xml_dom_Visitor_hpp__ */
