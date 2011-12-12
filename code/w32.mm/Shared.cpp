// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mm/Shared.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate ( ::LPCWSTR name, ::DWORD access, ::SIZE_T size )
    {
        const ::HANDLE handle = ::CreateFileMappingW(
                                    INVALID_HANDLE_VALUE, 0, access, 0, size, name
                                );
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreateFileMapping, ::GetLastError());
        }
        return (handle);
    }

    ::HANDLE open ( ::LPCWSTR name, ::DWORD access )
    {
        const ::HANDLE handle = ::OpenFileMappingW(access, FALSE, name);
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(OpenFileMapping,::GetLastError());
        }
        return (handle);
    }

    void * map ( ::HANDLE handle )
    {
        void *const location = ::MapViewOfFile(handle,FILE_MAP_ALL_ACCESS,0,0,0);
        if ( location == 0 ) {
            UNCHECKED_WIN32C_ERROR(MapViewOfFile,::GetLastError());
        }
        return (location);
    }

}

namespace w32 {
    namespace mm {

        Shared::Shared ( void * location )
            : myLocation(location)
        {
        }

        Shared::Shared ( const string& name )
            : Object(Object::claim(::open(name.c_str(), PAGE_READONLY))),
              myLocation(::map(handle()))
        {
        }

        Shared::Shared ( const string& name, size_t amount )
            : Object(Object::claim(
                         ::allocate(name.c_str(), PAGE_EXECUTE_READWRITE, amount)
                     )),
            myLocation(::map(handle()))
        {
        }

        void * Shared::location ()
        {
            return (myLocation);
        }

        const void * Shared::location () const
        {
            return (myLocation);
        }

    }
}
