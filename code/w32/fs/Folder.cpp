// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/Folder.hpp>
#include <w32/fs/Attributes.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ( ::LPCWSTR path, ::DWORD mode, ::DWORD attributes = 0 )
    {
        const ::DWORD access = GENERIC_READ|GENERIC_WRITE;
        const ::DWORD sharing = FILE_SHARE_READ|FILE_SHARE_WRITE;
        attributes |= FILE_FLAG_BACKUP_SEMANTICS;
        const ::HANDLE handle = ::CreateFileW(
            path, access, sharing, 0, mode, attributes, 0
            );
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFile, error);
        }
        return (handle);
    }

    ::DWORD cwdlen ()
    {
        ::WCHAR buffer[] = L"";
        const ::BOOL result = ::GetCurrentDirectoryW(0, buffer);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(GetCurrentDirectory, ::GetLastError());
        }
        return (result);
    }

}

namespace w32 { namespace fs {

    void Folder::create ( const string& path )
    {
        const ::BOOL result = ::CreateDirectoryExW(0, path.c_str(), 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ALREADY_EXISTS ) {
                return;
            }
            UNCHECKED_WIN32C_ERROR(CreateDirectory, error);
        }
    }

    void Folder::create ( const string& path, Transaction& transaction )
    {
        const ::BOOL result = ::CreateDirectoryTransactedW(
            0, path.data(), 0, transaction.handle()
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_ALREADY_EXISTS ) {
                return;
            }
            // ERROR_PATH_NOT_FOUND -> must create intermediate directories!
            UNCHECKED_WIN32C_ERROR(CreateDirectoryTransacted, error);
        }
    }

    void Folder::remove ( const string& path )
    {
        const ::BOOL result = ::RemoveDirectoryW(path.data());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RemoveDirectory, error);
        }
    }

    void Folder::remove ( const string& path, Transaction& transaction )
    {
        const ::BOOL result = ::RemoveDirectoryTransactedW
            (path.data(), transaction.handle());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RemoveDirectory, error);
        }
    }

    void Folder::current ( const string& path )
    {
        const ::BOOL result = ::SetCurrentDirectoryW(path.c_str());
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SetCurrentDirectory, error);
        }
    }

    string Folder::current ()
    {
        const ::DWORD length = cwdlen();
        ::WCHAR *const value = new ::WCHAR[length+1];
        value[length] = L'\0';
        const ::BOOL result = ::GetCurrentDirectoryW(length, value);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetCurrentDirectory, error);
        }
        return (string(string::box(value, length)));
    }

    bool Folder::is ( const string& path )
    {
        const Attributes attributes(path);
        return (!attributes.invalid() && attributes.folder());
    }

    Folder::Folder ( const string& path )
        : Object(claim(
              ::open(path.c_str(), OPEN_EXISTING)
              ))
    {
    }

    Folder::Folder ( const string& path, dword attributes )
        : Object(claim(
              ::open(path.c_str(), OPEN_EXISTING, attributes)
              ))
    {
    }

    string Folder::path () const
    {
        static const ::DWORD format = VOLUME_NAME_DOS;
        ::WCHAR path[MAX_PATH] = { 0 };
        const ::DWORD result = ::GetFinalPathNameByHandleW(
            handle(), path, sizeof(path)/sizeof(path[0])-1, format
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetFinalPathNameByHandle, error);
        }
        return (string(path, result));
    }

    ReparsePoint::ReparsePoint ( const string& path )
        : Folder(path, FILE_FLAG_OPEN_REPARSE_POINT)
    {
    }

} }

