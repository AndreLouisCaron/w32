// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mm/Mapping.hpp>
#include <w32/Error.hpp>

namespace {

    ::DWORD low ( ::DWORDLONG size ) {
        return (::DWORD(size&0x00000000ffffffff));
    }

    ::DWORD high ( ::DWORDLONG size ) {
        return (::DWORD((size&0xffffffff00000000)>>32));
    }

    ::HANDLE allocate ( ::HANDLE file, ::DWORDLONG size, ::DWORD mode )
    {
        const ::LPCWSTR name = 0;
        const ::HANDLE handle = ::CreateFileMappingW(
            file, 0, mode, high(size), low(size), name
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFileMapping, error);
        }
        return (handle);
    }

    ::LPVOID map
        ( ::HANDLE mapping, ::DWORDLONG offset, ::DWORD amount, ::DWORD mode )
    {
        const ::LPVOID data = ::MapViewOfFile(
            mapping, mode, high(offset), low(offset), amount
            );
        if ( data == 0 ) {
            const ::DWORD error = ::GetLastError();
            std::cerr << "MapViewOfFile() -> " << error << std::endl;
            if ( error == ERROR_MAPPED_ALIGNMENT ) {}
            UNCHECKED_WIN32C_ERROR(MapViewOfFile, error);
        }
        return (data);
    }

    void unmap ( ::LPVOID object )
    {
        const ::BOOL result = ::UnmapViewOfFile(object);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(UnmapViewOfFile, error);
        }
    }

    ::DWORD access ( ::DWORD mode, ::DWORD key )
    {
        static const ::DWORD _[2][2] = {
            { PAGE_READONLY,  FILE_MAP_READ  },
            { PAGE_READWRITE, FILE_MAP_WRITE },
        };
        return (_[mode][key]);
    }

}

namespace w32 { namespace mm {

    Mapping::Mapping( fs::File& file, Mode mode, qword size )
        : Object(claim(
              ::allocate(file.handle(), size, ::access(mode,0))
          )),
          myMode(mode)
    {
    }

    Mapping::Mode Mapping::mode () const
    {
        return (myMode);
    }

    Mapping::Mode Mapping::Mode::i ()
    {
        return (0);
    }

    Mapping::Mode Mapping::Mode::o ()
    {
        return (1);
    }

    Mapping::Mode::Mode ( Value value )
        : myValue(value)
    {
    }

    Mapping::Mode::Value Mapping::Mode::value () const
    {
        return (myValue);
    }

    Mapping::Mode::operator Mapping::Mode::Value () const
    {
        return (value());
    }

    Mapping::View::View ( Mapping& mapping, qword offset, dword amount )
        : myHandle(
              ::map(mapping.handle(), offset, amount,
              ::access(mapping.mode(),1)), &::unmap
              )
    {
    }

    void * Mapping::View::location ()
    {
        return (myHandle);
    }

    void Mapping::View::flush ( dword amount )
    {
        const ::BOOL result = ::FlushViewOfFile(myHandle, amount);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FlushViewOfFile, error);
        }
    }


} }
