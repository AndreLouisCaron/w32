// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/com/Object.hpp>
#include <w32/com/in-process-server.hpp>

namespace w32 { namespace com {

    Object::Object ()
        : myReferenceCount(1)
    {
        ::InterlockedIncrement(&GlobalObjectCount);
    }

    Object::~Object ()
    {
        ::InterlockedDecrement(&GlobalObjectCount);
    }

    ::ULONG __stdcall Object::AddRef ()
    {
        return (::InterlockedIncrement(&myReferenceCount));
    }

    ::ULONG __stdcall Object::Release ()
    {
        if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
        {
            delete this; return (0);
        }
        return (myReferenceCount);
    }

    ::HRESULT __stdcall Object::QueryInterface (
        const ::GUID& guid, void ** object
        )
    {
        (*object) = query< ::IUnknown >(guid);
        return ((*object) == 0)? E_NOINTERFACE : S_OK;
    }

} }
