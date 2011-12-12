// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.fs/File.hpp>
#include <w32.fs/Attributes.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE open ( ::LPCWSTR path, ::DWORD access = 0 )
    {
        const ::DWORD sharing = FILE_SHARE_READ|FILE_SHARE_WRITE;
        const ::DWORD mode = OPEN_EXISTING;
        const ::DWORD attributes = 0;
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

}

namespace w32 { namespace fs {

    void File::remove ( const string& path )
    {
        const ::BOOL result = ::DeleteFileW(path.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(DeleteFile, error);
        }
    }

    bool File::is ( const string& path )
    {
        const Attributes attributes(path);
        return (!attributes.invalid() && attributes.normal());
    }

    bool File::compressed ( const string& path )
    {
        const Attributes attributes(path);
        return (!attributes.invalid() && attributes.compressed());
    }

    void File::encrypt ( const string& path )
    {
        const ::BOOL result = ::EncryptFileW(path.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EncryptFile, error);
        }
    }

    void File::decrypt ( const string& path )
    {
        const ::BOOL result = ::DecryptFileW(path.data(), 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(DecryptFile, error);
        }
    }

    bool File::encrypted ( const string& path )
    {
        ::DWORD status = 0;
        const ::BOOL result = ::FileEncryptionStatusW(path.data(), &status);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FileEncryptionStatus, error);
        }
        return (FILE_IS_ENCRYPTED);
    }

    void File::prevent_encryption ( const string& path )
    {
        const ::BOOL result = ::EncryptionDisable(path.data(), TRUE);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(EncryptionDisable, error);
        }
    }

    File::File ( const string& path )
        : Object(claim(::open(path.data())))
    {
    }

    File::File ( const string& path, Access access )
        : Object(claim(::open(path.data(), access)))
    {
    }

    string File::path () const
    {
        static const ::DWORD format = VOLUME_NAME_DOS;
        ::WCHAR path[MAX_PATH] = { 0 };
        const ::DWORD result = ::GetFinalPathNameByHandleW(
            handle(), path, sizeof(path)/sizeof(path[0])-1, format
            );
        if ( result == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetFinalPathNameByHandle, error);
        }
        return (string(path, result));
    }

    void File::compress ()
    {
        // COMPRESSION_FORMAT_DEFAULT
        // COMPRESSION_FORMAT_LZNT1
        ::USHORT type = COMPRESSION_FORMAT_DEFAULT;
        ::DWORD returned = 0;
        const ::BOOL result = ::DeviceIoControl(
            handle(), FSCTL_SET_COMPRESSION, &type,
            sizeof(type), 0, 0, &returned, 0
            );
        if ( result == FALSE ) {
            throw (Error(::GetLastError()));
        }
    }

    void File::decompress ()
    {
        ::USHORT type = COMPRESSION_FORMAT_NONE;
        ::DWORD returned = 0;
        const ::BOOL result = ::DeviceIoControl(
            handle(), FSCTL_SET_COMPRESSION, &type,
            sizeof(type), 0, 0, &returned, 0
            );
        if ( result == FALSE ) {
            throw (Error(::GetLastError()));
        }
    }

    void File::sparsify ()
    {
        ::DWORD returned = 0;
        const ::BOOL result = ::DeviceIoControl(
            handle(), FSCTL_SET_SPARSE, 0, 0, 0, 0, &returned, 0
            );
        if ( result == FALSE ) {
            throw (Error(::GetLastError()));
        }
    }

    File::size_type File::size () const
    {
        ::LARGE_INTEGER size = { 0 };
        const ::BOOL result = ::GetFileSizeEx(handle(), &size);
        if ( result == FALSE ) {
            throw (Error(::GetLastError()));
        }
        return (size.QuadPart);
    }

        // make [from,to) available to the rest of the disk.
    void null_bytes ( ::HANDLE file, ::DWORD from, ::DWORD to )
    {
            // Specify range.
        ::FILE_ZERO_DATA_INFORMATION zeros;
        ::ZeroMemory(&zeros, sizeof(zeros));
        zeros.FileOffset.QuadPart = from;
        zeros.BeyondFinalZero.QuadPart = to;
        
            // Make it free!
        ::DWORD returned = 0;
        const ::BOOL result = ::DeviceIoControl(
            file, FSCTL_SET_ZERO_DATA, &zeros, sizeof(zeros), 0, 0, &returned, 0
            );
        if ( result == FALSE ) {
            throw (Error(::GetLastError()));
        }
    }

    void walk_allocated_ranges ( ::HANDLE file )
    {
            // Specify range of interest (whole file).
        ::FILE_ALLOCATED_RANGE_BUFFER ranges;
        ::ZeroMemory(&ranges, sizeof(ranges));
        ranges.FileOffset.QuadPart = 0;
        ::GetFileSizeEx(file, &ranges.Length);
        
            // Allocate buffer for list of blocks...
        ::BYTE data[1024] = { 0 }; 
        
            // Query the list.
        ::DWORD returned = 0;
        const ::BOOL result = ::DeviceIoControl(
            file, FSCTL_QUERY_ALLOCATED_RANGES, &ranges,
            sizeof(ranges), data, sizeof(data), &returned, 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_INSUFFICIENT_BUFFER )
            {
                // Allocate a bigger buffer.
            }
            else if ( error == ERROR_MORE_DATA )
            {
                // Process returned results using 'returned' bytes.
                // Compute offset until last processed range.
                // Call again specifying new offset to get new results.
            }
            else {
                throw (Error(::GetLastError()));
            }
        }
        // How do we iterate over the returned ranges?
    }

        // Enumerate alternate data streams (>= Windows 2000)!
    void streams ( ::HANDLE file )
    {
        const ::DWORD header =
            offsetof(::WIN32_STREAM_ID, cStreamName);
        ::WIN32_STREAM_ID stream;
        ::ZeroMemory(&stream, sizeof(stream));
        ::BOOL result = FALSE;
        ::BOOL enumerate = FALSE;
        ::LPVOID context = 0;
        ::DWORD returned = 0;
        do {
                // Read stream header.
            result = ::BackupRead(
                file, (::LPBYTE)&stream, header, &returned, 0, 0, &context
                );
            if ( result == FALSE ) { throw (Error(::GetLastError())); }
            if ( returned == 0 ) return;
            
                // Query stream name.
            ::WCHAR name[MAX_PATH] = { 0 };
            result = ::BackupRead(
                file, (::LPBYTE)name, stream.dwStreamNameSize,
                &returned, 0, 0, &context
                );
            if ( result == FALSE ) { throw (Error(::GetLastError())); }
            if ( returned == 0 ) {
                ::wcscpy(name, L"::$DATA");
            }
            
                // Skip stream data.
            ::DWORD seeked[2] = { 0 }; // LARGE_INTEGER...
            result = ::BackupSeek(
                file, stream.Size.LowPart, stream.Size.HighPart,
                &seeked[0], &seeked[1], &context
                );
            if ( result == FALSE ) { throw (Error(::GetLastError())); }
            
            std::wcout << name << std::endl;
        }
        while ( true );
        
            // Release backup context!
        result = ::BackupRead(
            file, 0, 0, 0, TRUE, 0, &context
            );
        if ( result == FALSE ) { throw (Error(::GetLastError())); }
    }

        // Enumerate data streams (>= Windows Vista).
        // Could be implementing using ::reference()/::cleanup()
        // on earlier systems.
    void streams ( ::LPCWSTR path )
    {
        const ::STREAM_INFO_LEVELS level = ::FindStreamInfoStandard;
        
            // Find the first match.
        ::WIN32_FIND_STREAM_DATA stream;
        ::ZeroMemory(&stream, sizeof(stream));
        const ::HANDLE search = ::FindFirstStreamW(path, level, &stream, 0);
        if ( search == INVALID_HANDLE_VALUE ) {
            throw (Error(::GetLastError()));
        }
        
        std::wcout << stream.cStreamName << std::endl;
        
            // Process other results...
        ::BOOL result = FALSE;
        do {
            result = ::FindNextStreamW(search, &stream);
            if ( result == FALSE )
            {
                const ::DWORD error = ::GetLastError();
                if ( error == ERROR_HANDLE_EOF ) break;
                throw (Error(error));
            }
            std::wcout << stream.cStreamName << std::endl;
        }
        while ( result != FALSE );
        
            // Release search resources.
        result = ::FindClose(search);
        if ( result == FALSE ) { throw (Error(::GetLastError())); }
    }

    File::Access File::Access::i ()
    {
        return (GENERIC_READ);
    }

    File::Access File::Access::o ()
    {
        return (GENERIC_WRITE);
    }

    File::Access::Access ( Value value )
        : myValue(value)
    {
    }

    File::Access::Value File::Access::value () const
    {
        return (myValue);
    }

    File::Access::operator File::Access::Value () const
    {
        return (value());
    }

} }
