#ifndef _w32_xml_sax_Reader_hpp__
#define _w32_xml_sax_Reader_hpp__

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
