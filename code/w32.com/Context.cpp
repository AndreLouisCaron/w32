// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.com/Context.hpp>

namespace w32 { namespace com {

    const Context Context::inprocess ()
    {
        return (CLSCTX_INPROC_SERVER);
    }

    const Context Context::local ()
    {
        return (CLSCTX_LOCAL_SERVER);
    }

    const Context Context::remote ()
    {
        return (CLSCTX_REMOTE_SERVER);
    }

    Context::Context ( Value value )
        : myValue(value)
    {
    }

    Context::Value Context::value () const
    {
        return (myValue);
    }

    Context::operator Context::Value () const
    {
        return (myValue);
    }

} }
