#ifndef _w32_xml_sax_ErrorHandler_hpp__
#define _w32_xml_sax_ErrorHandler_hpp__

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
