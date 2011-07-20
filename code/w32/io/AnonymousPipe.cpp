// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/io/AnonymousPipe.hpp>
#include <w32/Error.hpp>

namespace {

    void allocate ( ::PHANDLE input, ::PHANDLE output )
    {
        (*output) = (*input) = INVALID_HANDLE_VALUE;
        const ::BOOL result = ::CreatePipe(input, output, 0, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreatePipe, error);
        }
    }

}

namespace w32 { namespace io {

    AnonymousPipe::Handles::Handles ()
    {
        allocate(&input, &output);
    }

    AnonymousPipe::Output::Output ( const Handles& handles )
        : Stream(Object::claim(handles.output))
    {
    }

    AnonymousPipe::Input::Input ( const Handles& handles )
        : Stream(Object::claim(handles.input))
    {
    }

    AnonymousPipe::AnonymousPipe ()
        : myHandles(),
          myInput(myHandles),
          myOutput(myHandles)
    {
    }

} }
