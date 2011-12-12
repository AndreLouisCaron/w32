#ifndef _w32_xml_sax_DtdHandler_hpp__
#define _w32_xml_sax_DtdHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.xml.sax/Locator.hpp>

namespace w32 { namespace xml { namespace sax {

    typedef com::Ptr< ::ISAXDTDHandler > DtdHandler;

    class BasicDtdHandler :
        public com::Model< ::ISAXDTDHandler >
    {
        /* methods. */
    public:

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall notationDecl
            (  const wchar_t * name, int nlen,
               const wchar_t * publicID, int plen,
               const wchar_t * systemID, int slen )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall unparsedEntityDecl
            (  const wchar_t * name, int nlen,
               const wchar_t * publicID, int plen,
               const wchar_t * systemID, int slen,
               const wchar_t * notationName, int nnlen )
        {
            return (S_OK);
        }
    };

} } }

#endif /* _w32_xml_sax_DtdHandler_hpp__ */
