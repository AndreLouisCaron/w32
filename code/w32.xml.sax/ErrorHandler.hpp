#ifndef _w32_xml_sax_ErrorHandler_hpp__
#define _w32_xml_sax_ErrorHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.xml.sax/Locator.hpp>

namespace w32 { namespace xml { namespace sax {

    typedef com::Ptr< ::ISAXErrorHandler > ErrorHandler;

    class BasicErrorHandler :
        public com::Model< ::ISAXErrorHandler >
    {
        /* methods. */
    public:
        virtual void fail
            ( const string& message, com::Result code, Locator locator )
        {}
        virtual void warn
            ( const string& message, com::Result code, Locator locator )
        {}

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall error
            ( ::ISAXLocator * locator, ::LPCWSTR message, ::HRESULT code )
        {
            this->fail(string(message), code, com::manage(locator));
            return (S_OK);
        }
        
        virtual ::HRESULT __stdcall fatalError
            ( ::ISAXLocator * locator, ::LPCWSTR message, ::HRESULT code )
        {
            this->fail(string(message), code, com::manage(locator));
            return (S_OK);
        }
        
        virtual ::HRESULT __stdcall ignorableWarning
            (  ::ISAXLocator * locator, ::LPCWSTR message, ::HRESULT code )
        {
            this->warn(string(message), code, com::manage(locator));
            return (S_OK);
        }
    };

} } }

#endif /* _w32_xml_sax_ErrorHandler_hpp__ */
