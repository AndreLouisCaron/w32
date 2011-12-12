#ifndef _w32_xml_sax_Reader_hpp__
#define _w32_xml_sax_Reader_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.hpp>
#include <w32.xml.sax/ContentHandler.hpp>
#include <w32.xml.sax/DtdHandler.hpp>
#include <w32.xml.sax/ErrorHandler.hpp>
#include <w32.xml.sax/LexicalHandler.hpp>

namespace w32 { namespace xml { namespace sax {

    typedef com::Ptr< ::ISAXXMLReader > Reader;

    Reader new_reader ( const com::Library& )
    {
        ::ISAXXMLReader * reader = 0;
        const com::Result result = ::CoCreateInstance(
            __uuidof(SAXXMLReader60), 0, CLSCTX_ALL,
            __uuidof(ISAXXMLReader), (void **)&reader
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, CoCreateInstance, result);
        }
        return (Reader(reader));
    }

    void put ( Reader reader, ErrorHandler handler )
    {
        const com::Result result = reader->putErrorHandler(handler.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, putErrorHandler, result);
        }
    }

    void put ( Reader reader, DtdHandler handler )
    {
        const com::Result result = reader->putDTDHandler(handler.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, putDtdHandler, result);
        }
    }

    void put ( Reader reader, ContentHandler handler )
    {
        const com::Result result = reader->putContentHandler(handler.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, putContentHandler, result);
        }
    }

    void feature ( Reader reader, const string& name, bool enable )
    {
        const ::VARIANT_BOOL state = (enable)? VARIANT_TRUE : VARIANT_FALSE;
        const com::Result result = reader->putFeature(name.data(), state);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, putFeature, result);
        }
    }

    void property_ ( Reader reader, const string& name, LexicalHandler handler )
    {
        w32::Variant variant; variant = handler.value();
        const com::Result result =
            reader->putProperty(name.data(), variant.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, putProperty, result);
        }
    }

    void baseurl ( Reader reader, const string& url )
    {
        const com::Result result = reader->putBaseURL(url.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, parseURL, result);
        }
    }

    void parse ( Reader reader, const string& url )
    {
        const com::Result result = reader->parseURL(url.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLReader, parseURL, result);
        }
    }

} } }

#endif /* _w32_xml_sax_Reader_hpp__ */
