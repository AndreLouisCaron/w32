// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl.ext/Extension.hpp>

namespace w32 { namespace shl { namespace ext {

    Extension::~Extension ()
    {
    }

    const com::Ptr< ::IDataObject >& Extension::data () const
    {
        return (myData);
    }

    ::HRESULT __stdcall Extension::Initialize (
        ::LPCITEMIDLIST path, ::IDataObject * object, ::HKEY
        )
    {
        myPath = path;
        myData = com::manage(object);
        return (S_OK);
    }

} } }
