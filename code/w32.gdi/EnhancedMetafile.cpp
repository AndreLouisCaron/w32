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

#include <w32.gdi/EnhancedMetafile.hpp>
#include <w32.gdi/Rectangle.hpp>
#include <w32.gdi/Size.hpp>
#include <w32/string.hpp>
#include <w32/Error.hpp>

namespace {

    ::HENHMETAFILE open ( ::LPCWSTR path )
    {
        const ::HENHMETAFILE handle = ::GetEnhMetaFileW(path);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (handle);
    }

    ::HDC create (
        const ::SIZE& size, ::LPCWSTR path, ::LPCWSTR description, ::HDC device
        )
    {
        const int wm = ::GetDeviceCaps(device, HORZSIZE);
        const int hm = ::GetDeviceCaps(device, VERTSIZE);
        const int wp = ::GetDeviceCaps(device, HORZRES);
        const int hp = ::GetDeviceCaps(device, VERTRES);
        const ::RECT area = {
            0, 0, (size.cx * wm * 100) / wp, (size.cy * hm * 100) / hp
        };
        const ::HDC handle = ::CreateEnhMetaFileW
            (device, path, &area, description);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (0);
    }

    ::HENHMETAFILE close ( ::HDC object )
    {
        const ::HENHMETAFILE handle = ::CloseEnhMetaFile(object);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetEnhMetaFile, error);
        }
        return (handle);
    }

    void abandon ( ::HENHMETAFILE object ) {}
    void destroy ( ::HENHMETAFILE object )
    {
        const ::BOOL result = ::DeleteEnhMetaFile(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace gdi {

    EnhancedMetafile::Handle EnhancedMetafile::claim ( ::HENHMETAFILE object )
    {
        return (Handle(object, &::destroy));
    }

    EnhancedMetafile::Handle EnhancedMetafile::proxy ( ::HENHMETAFILE object )
    {
        return (Handle(object, &::abandon));
    }

        static EnhancedMetafile open ( const string& path );

    EnhancedMetafile::EnhancedMetafile ( const Handle& handle )
        : myHandle(handle)
    {
    }

#if 0
    EnhancedMetafile::EnhancedMetafile ( const Size& size, const string& path )
        : myHandle(claim(::create(
              size.data(), path.data(), 0, 0
              )))
    {
    }

    EnhancedMetafile::EnhancedMetafile
        ( const Size& size, const string& path, const string& description )
        : myHandle(claim(::create(
              size.data(), path.data(), description.data(), 0
              )))
    {
    }
#endif

    const EnhancedMetafile::Handle& EnhancedMetafile::handle () const
    {
        return (myHandle);
    }

} }
