// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Resource.hpp>

namespace {

    void abandon ( ::LPCWSTR ) {}
    void destroy ( ::LPCWSTR object )
    {
        ::free(const_cast<::LPWSTR>(object));
    }

    w32::Resource::Identifier reference ( int number )
    {
        return (w32::Resource::Identifier(MAKEINTRESOURCEW(number), &abandon));
    }

    w32::Resource::Identifier reference ( ::LPCWSTR name )
    {
        return (w32::Resource::Identifier(::_wcsdup(name), &destroy));
    }

}

namespace w32 {

    Resource::Resource ( const Module& module, const string& name )
        : myModule(module), myIdentifier(::reference(name.data()))
    {
    }

    Resource::Resource ( const Module& module, int number )
        : myModule(module), myIdentifier(::reference(number))
    {
    }

    const Module& Resource::module () const
    {
        return (myModule);
    }

    const Resource::Identifier& Resource::identifier () const
    {
        return (myIdentifier);
    }

}
