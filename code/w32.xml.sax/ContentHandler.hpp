#ifndef _w32_xml_sax_ContentHandler_hpp__
#define _w32_xml_sax_ContentHandler_hpp__

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
#include <w32.xml.sax/Attributes.hpp>

namespace w32 { namespace xml { namespace sax {

    typedef com::Ptr< ::ISAXContentHandler > ContentHandler;

    class BasicContentHandler :
        public com::Model< ::ISAXContentHandler >
    {
        /* methods. */
    public:
        virtual void begin () {}
        virtual void end () {}
        virtual void open ( const string& tag, Attributes attributes ) {}
        virtual void close () {}
        virtual void skip ( const string& entity ) {}
        virtual void attribute
            ( const string& key, const string& value ) {}
        virtual void ignore
            ( const string& data ) {}
        virtual void data
            ( const string& text ) {}

        /* overrides .*/
    public:
        virtual ::HRESULT __stdcall putDocumentLocator
            ( ::ISAXLocator * locator )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall startDocument ()
        {
            this->begin();
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endDocument ()
        {
            this->end();
            return (S_OK);
        }

        virtual ::HRESULT __stdcall startPrefixMapping
            ( ::LPCWSTR prefix, int plen, ::LPCWSTR uri, int ulen )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endPrefixMapping
            ( ::LPCWSTR prefix, int plen )
        {
            return (S_OK);
        }

        virtual ::HRESULT __stdcall startElement
            ( ::LPCWSTR uri, int ulen, ::LPCWSTR lname, int llen,
            ::LPCWSTR qname, int qlen, ::ISAXAttributes * attributes )
        {
            //this->open(string(uri,ulen));
            this->open(string(lname,llen), com::manage(attributes));
            //this->open(string(qname,qlen));
            return (S_OK);
        }

        virtual ::HRESULT __stdcall endElement
            ( ::LPCWSTR uri, int ulen, ::LPCWSTR lname, int llen,
            ::LPCWSTR qname, int qlen )
        {
            this->close();
            return (S_OK);
        }

        virtual ::HRESULT __stdcall characters
            ( ::LPCWSTR data, int length )
        {
            this->data(string(data));
            return (S_OK);
        }

        virtual ::HRESULT __stdcall ignorableWhitespace
            ( ::LPCWSTR data, int length )
        {
            this->ignore(string(data));
            return (S_OK);
        }

        virtual ::HRESULT __stdcall processingInstruction
            ( ::LPCWSTR key, int klen, ::LPCWSTR val, int vlen )
        {
            this->attribute(string(key), string(val));
            return (S_OK);
        }

        virtual ::HRESULT __stdcall skippedEntity
            ( ::LPCWSTR name, int length )
        {
            this->skip(string(name));
            return (S_OK);
        }
    };

} } }

#endif /* _w32_xml_sax_ContentHandler_hpp__ */
