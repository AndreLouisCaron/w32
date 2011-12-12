#ifndef _w32_xml_dom_walk_hpp__
#define _w32_xml_dom_walk_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.xml.dom/Node.hpp>

namespace w32 { namespace xml { namespace dom {

        /*!
         * @brief Pre-order traversal of a DOM tree.
         */
    template<typename Visitor>
    void walk ( Node node, Visitor visit )
    {
        while ( node.get() != 0 )
        {
                // Visit the node itself.
            visit(node);
            
                // Visit all descendants.
            walk(node.first(), visit);
            
                // Move to next sibling.
            node = node.next();
        }
    }

} } }

#endif /* _w32_xml_dom_walk_hpp__ */
