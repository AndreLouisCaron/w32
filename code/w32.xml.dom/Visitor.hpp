#ifndef _w32_xml_dom_Visitor_hpp__
#define _w32_xml_dom_Visitor_hpp__

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
