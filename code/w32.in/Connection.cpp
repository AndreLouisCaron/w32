// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.in/Connection.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    void abandon ( ::HINTERNET object ) {}
    void destroy ( ::HINTERNET object )
    {
        const ::BOOL result = ::InternetCloseHandle(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace in {

    const Connection::Handle Connection::claim ( ::HINTERNET object )
    {
        return (Handle(object, &::destroy));
    }

    const Connection::Handle Connection::proxy ( ::HINTERNET object )
    {
        return (Handle(object, &::abandon));
    }

    Connection::Connection ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Connection::Handle& Connection::handle () const
    {
        return (myHandle);
    }

} }
