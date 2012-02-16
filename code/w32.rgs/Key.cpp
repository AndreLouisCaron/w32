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

#include <w32.rgs/Key.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    static ::HKEY create (
        ::HKEY parent, const wchar_t * path, ::REGSAM access
        )
    {
        ::DWORD disposition = 0;
        ::HKEY handle = 0;
        const ::LONG result = ::RegCreateKeyExW(
            parent, path, 0, 0, REG_OPTION_NON_VOLATILE,
            access, 0, &handle, &disposition
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegOpenKeyEx,result);
        }
        return (handle);
    }

    ::HKEY open ( ::HKEY parent, ::LPCWSTR path, ::REGSAM access )
    {
        ::HKEY handle = 0;
        const ::LONG result = ::RegOpenKeyExW(
            parent, path, 0, access, &handle
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_FILE_NOT_FOUND ) {
            }
            UNCHECKED_WIN32C_ERROR(RegOpenKeyEx,result);
        }
        return (handle);
    }

    void destroy ( ::HKEY object )
    {
        const ::LONG result = ::RegCloseKey(object);
        if ( result != ERROR_SUCCESS )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HKEY object )
    {
    }

}

namespace w32 { namespace rgs {

    Key::Handle Key::claim ( ::HKEY object )
    {
        return (Key::Handle(object, &destroy));
    }

    Key::Handle Key::proxy ( ::HKEY object )
    {
        return (Key::Handle(object, &abandon));
    }

    Key Key::create ( const Key& parent, const string& path )
    {
        const Handle handle(claim(
            ::create(parent.handle(), path.c_str(), KEY_ALL_ACCESS)
            ));
        return (Key(handle));
    }

    Key Key::create (
        const Key& parent, const string& path, const string& value
        )
    {
        Key result = create(parent, path);
        result = value;
        return (result);
    }

    const Key Key::machine ()
    {
        return (Key(proxy(HKEY_LOCAL_MACHINE)));
    }

    const Key Key::user ()
    {
        return (Key(proxy(HKEY_CURRENT_USER)));
    }

    const Key Key::users ()
    {
        return (Key(proxy(HKEY_USERS)));
    }

    const Key Key::classes ()
    {
        return (Key(proxy(HKEY_CLASSES_ROOT)));
    }

#if (_WIN32_WINNT  >= 0x0600)
    const Key Key::configuration ()
    {
        return (Key(proxy(HKEY_CURRENT_CONFIG)));
    }
#endif

    Key::Key ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Key::Key (
        const Key& parent, const string& path, const Access& access
        )
        : myHandle(claim(::open(parent.handle(), path.data(), access)))
    {
    }

    const Key::Handle& Key::handle () const
    {
        return (myHandle);
    }

    void Key::flush ()
    {
        const ::LONG result = ::RegFlushKey(handle());
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegFlushKey,result);
        }
    }

    void Key::remove ( const string& value )
    {
        const ::LONG result = ::RegDeleteValueW(handle(),value.data());
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegDeleteValue,result);
        }
    }

    void Key::delete_ ( const string& subkey )
    {
        const ::LONG result = ::RegDeleteKeyW(handle(), subkey.data());
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegDeleteKey,result);
        }
    }

    Key& Key::operator= ( const string& value )
    {
        const ::LONG result = ::RegSetValueExW(
            handle(), 0, 0, REG_SZ,
            (const ::BYTE*)value.c_str(), ::DWORD(value.length()+1)
            );
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegSetValueEx,result);
        }
        return (*this);
    }

} }
