// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32/Module.hpp>
#include <w32/Error.hpp>

    // Require process status API for "GetModuleBaseName()".
#include "../w32.ipc/__configure__.hpp"

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
