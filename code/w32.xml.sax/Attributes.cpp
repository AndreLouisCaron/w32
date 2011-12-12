// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
