// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Object.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::CloseHandle(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HANDLE )
    {
    }

}

namespace w32 {

    Object::Handle Object::claim ( ::HANDLE object )
    {
        return (Handle(object, &release));
    }

    Object::Handle Object::proxy ( ::HANDLE object )
    {
        return (Handle(object, &abandon));
    }

    Object::Object ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Object::Object ()
        : myHandle(proxy(0))
    {
    }

    Object::~Object ()
    {
    }

    const Object::Handle& Object::handle () const
    {
        return (myHandle);
    }

    void Object::destroy ()
    {
        myHandle = proxy(0);
    }

}
