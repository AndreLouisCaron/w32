// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/Guid.hpp>
#include <iostream>
#include <string.h>

namespace w32 { namespace msi {

    Guid::Guid ( const wchar_t * value )
    {
        myValue[38] = L'\0';
        ::wcsncpy(myValue,value,38);
    }

    string Guid::value () const
    {
        return (myValue);
    }

    std::wostream& operator<< ( std::wostream& out, const Guid& guid )
    {
        return (out << guid.value());
    }

} }
