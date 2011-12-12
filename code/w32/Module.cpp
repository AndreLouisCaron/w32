// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/Module.hpp>
#include <w32/Error.hpp>

    // Require process status API for "GetModuleBaseName()".
#include "../w32.ipc/__configure__.hpp"
#ifdef _MSC_VER
#   pragma comment ( lib, "PSApi.lib" )
#endif

namespace {

    ::HMODULE current ()
    {
        return (::GetModuleHandleW(0));
    }

    ::HMODULE find ( ::LPCWSTR name )
    {
        const ::HANDLE result = ::GetModuleHandleW(name);
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetModuleHandle, error);
        }
        return (static_cast<::HMODULE>(result));
    }

    ::HMODULE load ( ::LPCWSTR path )
    {
        const ::HMODULE module = ::LoadLibraryW(path);
        if ( module == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadLibrary, error);
        }
        return (module);
    }

    void release ( ::HMODULE object )
    {
        if ( ::FreeLibrary(object) == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FreeLibrary, error);
        }
    }

    void abandon ( ::HMODULE object )
    {
    }

}

namespace w32 {

    Module::Handle Module::claim ( ::HMODULE object )
    {
        return (Handle(object, &::release));
    }

    Module::Handle Module::proxy ( ::HMODULE object )
    {
        return (Handle(object, &::abandon));
    }

    Module Module::load ( const string& path )
    {
        return (Module(claim(::load(path.data()))));
    }

    Module::Module ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Module::Module ()
        : myHandle(proxy(::current()))
    {
    }

    Module::Module ( const string& name )
        : myHandle(proxy(find(name.data())))
    {
    }

    const Module::Handle& Module::handle () const
    {
        return (myHandle);
    }

    string Module::name () const
    {
        wchar_t value[MAX_PATH+1];
        const dword result = ::GetModuleBaseNameW(
            ::GetCurrentProcess(), myHandle, value, MAX_PATH
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetModuleBaseName, error);
        }
        value[result] = L'\0';
        return (value);
    }

    string Module::path () const
    {
        wchar_t value[MAX_PATH+1];
        const dword result = ::GetModuleFileNameW(
            myHandle, value, MAX_PATH
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetModuleFileName, error);
        }
        value[result] = L'\0';
        return (value);
    }

    void * Module::get ( const astring& symbol ) const
    {
        ::FARPROC address = ::GetProcAddress(myHandle, symbol.c_str());
        return (*reinterpret_cast<void**>(&address));
    }

}
