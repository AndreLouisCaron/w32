// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/Channel.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/Channel.hpp>
#include <w32.io/InputStream.hpp>
#include <w32.io/OutputStream.hpp>

namespace w32 { namespace io {

    Channel::Channel ( const Handle& handle )
        : Object(handle)
    {
    }

    dword Channel::get ( byte * data, dword size )
    {
        return (InputStream(*this).get(data, size));
    }

    dword Channel::put ( const byte * data, dword size )
    {
        return (OutputStream(*this).put(data, size));
    }

    Channel::operator InputStream () const
    {
        return (InputStream(handle()));
    }

    Channel::operator OutputStream () const
    {
        return (OutputStream(handle()));
    }

} }
