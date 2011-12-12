#ifndef _w32_xml_dom_Instruction_hpp__
#define _w32_xml_dom_Instruction_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class Instruction
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMProcessingInstruction > Ptr;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        Instruction ( const Ptr& ptr );

        /* methods. */
    public:
        Ptr get () const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMProcessingInstruction > ()
{
    return (IID_IXMLDOMProcessingInstruction);
}

#endif /* _w32_xml_dom_Instruction_hpp__ */
