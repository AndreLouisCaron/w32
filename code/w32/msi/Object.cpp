// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/Object.hpp>
#include <w32/msi/Error.hpp>

namespace {

    void abandon ( ::MSIHANDLE object )
    {
    }

    void destroy ( ::MSIHANDLE object )
    {
            // Return the resource to the system.
        const ::UINT result = ::MsiCloseHandle(object);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_HANDLE ) {
            }
            UNCHECKED_INSTALLER_ERROR(MsiCloseHandle, result);
        }
    }

}

namespace w32 { namespace msi {

    Object::Handle Object::claim ( ::MSIHANDLE object )
    {
        return (Object::Handle(object, &::destroy));
    }

    Object::Handle Object::proxy ( ::MSIHANDLE object )
    {
        return (Object::Handle(object, &::abandon));
    }

    Object::Object ( const Handle& handle )
        : myHandle(handle)
    {
    }

    const Object::Handle& Object::handle () const
    {
        return (myHandle);
    }

} }
