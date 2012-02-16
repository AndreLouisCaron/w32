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
