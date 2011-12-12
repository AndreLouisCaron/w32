// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
