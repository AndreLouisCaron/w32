#ifndef _w32_xml_dom_CData_hpp__
#define _w32_xml_dom_CData_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace dom {

    class W32_XML_DOM_EXPORT CData
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::IXMLDOMCDATASection > Ptr;

        /* data. */
    private:
        Ptr myPtr;

        /* construction. */
    public:
        CData ( const Ptr& ptr );

        /* methods. */
    public:
        Ptr get () const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IXMLDOMCDATASection > ()
{
    return (IID_IXMLDOMCDATASection);
}

#endif /* _w32_xml_dom_CData_hpp__ */
