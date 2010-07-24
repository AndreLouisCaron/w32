// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/com/Result.hpp>

namespace w32{ namespace com {

    const Result Result::success ()
    {
        return (S_OK);
    }

    const Result Result::failure ()
    {
        return (E_FAIL);
    }

    const Result Result::invalid ()
    {
        return (E_INVALIDARG);
    }

    const Result Result::false_ ()
    {
        return (S_FALSE);
    }

    const Result Result::outofmemory ()
    {
        return (E_OUTOFMEMORY);
    }

} }
