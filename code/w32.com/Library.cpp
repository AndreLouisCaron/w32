// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.com/Library.hpp>
#include <w32.com/Error.hpp>
#include <w32.com/Result.hpp>

namespace w32{ namespace com {

    Library::Library ( const Threading& model )
    {
        const Result result = ::CoInitializeEx(0, model.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(COM,CoInitializeEx,result);
        }
    }

    Library::~Library ()
    {
        ::CoUninitialize();
    }

} }
