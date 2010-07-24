#ifndef _w32_xml_sax_Attributes_hpp__
#define _w32_xml_sax_Attributes_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace xml { namespace sax {

    class W32_XML_SAX_EXPORT Attributes
    {
        /* nested types. */
    public:
        typedef com::Ptr< ::ISAXAttributes > Ptr;

        /* data. */
    private:
        Ptr myBackend;

        /* construction. */
    public:
        Attributes ( const Ptr& backend );

        /* methods. */
    public:
        int length () const;
        int index ( const string& name ) const;
        string name ( int index ) const;

        /* operators. */
    public:
        string operator[] ( int index ) const;
        string operator[] ( const string& name ) const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof<::ISAXAttributes> ()
{
    return (IID_ISAXAttributes);
}

#endif /* _w32_xml_sax_Attributes_hpp__ */
