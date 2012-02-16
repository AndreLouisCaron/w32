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

#include <w32.xml.sax/Attributes.hpp>

namespace w32 { namespace xml { namespace sax {

    Attributes::Attributes ( const Ptr& backend )
        : myBackend(backend)
    {
    }

    int Attributes::length () const
    {
        int length = 0;
        const com::Result result = myBackend->getLength(&length);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLAttributes, getLength, result);
        }
        return (length);
    }

    int Attributes::index ( const string& name ) const
    {
        int index = 0;
        const com::Result result = myBackend->getIndexFromName(
            L"", 0, name.data(), name.length(), &index
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLAttributes, getIndexFromName, result);
        }
        return (index);
    }

    string Attributes::name ( int index ) const
    {
        ::LPCWSTR uri = 0; int ulen = 0;
        ::LPCWSTR lname = 0; int llen = 0;
        ::LPCWSTR qname = 0; int qlen = 0;
        const com::Result result = myBackend->getName(
            index, &uri, &ulen, &lname, &llen, &qname, &qlen
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLAttributes, getName, result);
        }
        return (string(lname, llen));
    }

    string Attributes::operator[] ( int index ) const
    {
        ::LPCWSTR value = 0; int length = 0;
        const com::Result result = myBackend->getValue(
            index, &value, &length
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLAttributes, getValue, result);
        }
        return (string(value, length));
    }

    string Attributes::operator[] ( const string& name ) const
    {
        ::LPCWSTR value = 0; int length = 0;
        const com::Result result = myBackend->getValueFromName(
            L"", 0, name.data(), name.length(), &value, &length
            );
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ISAXXMLAttributes, getValueFromName, result);
        }
        return (string(value, length));
    }

} } }
