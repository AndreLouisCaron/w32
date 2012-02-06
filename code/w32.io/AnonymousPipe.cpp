// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/AnonymousPipe.cpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include <w32.io/AnonymousPipe.hpp>
#include <w32/Error.hpp>

namespace {

    void allocate ( ::PHANDLE input, ::PHANDLE output )
    {
        ::SECURITY_ATTRIBUTES attributes;
        attributes.nLength = sizeof(attributes);
        attributes.lpSecurityDescriptor = 0;
        attributes.bInheritHandle = TRUE;
        const ::BOOL result = ::CreatePipe(input, output, &attributes, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePipe, error);
        }
    }

}

namespace w32 { namespace io {

    AnonymousPipe::AnonymousPipe ()
    {
            // Allocate handles.
        ::HANDLE handles[2] = { 0 };
        allocate(&handles[0], &handles[1]);
            // Wrap them.
        myHandles[0] = Object::claim(handles[0]);
        myHandles[1] = Object::claim(handles[1]);
    }

    AnonymousPipe::operator InputStream () const
    {
        return (InputStream(myHandles[0]));
    }

    AnonymousPipe::operator OutputStream () const
    {
        return (OutputStream(myHandles[1]));
    }

} }
