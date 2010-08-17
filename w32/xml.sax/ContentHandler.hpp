#ifndef _w32_xml_sax_ContentHandler_hpp__
#define _w32_xml_sax_ContentHandler_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/xml.sax/Attributes.hpp>

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
