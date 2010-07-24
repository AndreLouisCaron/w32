#ifndef _w32_xml_sax_Locator_hpp__
#define _w32_xml_sax_Locator_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace sax {

    class W32_XML_SAX_EXPORT Locator
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::ISAXLocator > Ptr;

        /* data. */
    private:
        Ptr myBackend;

        /* construction. */
    public:
        Locator ( const Ptr& backend );

        /* methods. */
    public:
        int line () const;
        int column () const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof<::ISAXLocator> ()
{
    return (IID_ISAXLocator);
}


#endif /* _w32_xml_sax_Locator_hpp__ */
