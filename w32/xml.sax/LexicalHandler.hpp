#ifndef _w32_xml_sax_LexicalHandler_hpp__
#define _w32_xml_sax_LexicalHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/xml.sax/Locator.hpp>

namespace w32 { namespace xml { namespace sax {

    typedef com::Ptr< ::ISAXLexicalHandler > LexicalHandler;

    class BasicLexicalHandler :
        public com::Model< ::ISAXLexicalHandler >
    {
        /* methods. */
    public:

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall startDTD
            (  const wchar_t * name, int nlen,
               const wchar_t * publicID, int plen,
               const wchar_t * systemID, int slen )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endDTD ()
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall comment
            (  const wchar_t * data, int len )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall startCDATA ()
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endCDATA ()
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall startEntity ( const wchar_t * name, int nlen )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endEntity ( const wchar_t * name, int nlen )
        {
            return (S_OK);
        }
    };

} } }

#endif /* _w32_xml_sax_LexicalHandler_hpp__ */
