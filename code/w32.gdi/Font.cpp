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

#include <w32.gdi/Font.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HFONT load ( int name )
    {
        const ::HGDIOBJ handle = ::GetStockObject(name);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetStockObject, error);
        }
        return (static_cast< ::HFONT >(handle));
    }

    ::HFONT create ( const ::LOGFONTW& attributes )
    {
        const ::HFONT handle = ::CreateFontIndirectW(&attributes);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateFontIndirect, error);
        }
        return (handle);
    }

    void destroy ( ::HFONT object )
    {
        const ::BOOL result = ::DeleteObject(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HFONT object )
    {
    }

}

namespace w32 { namespace gdi {

    Font::Handle Font::claim ( ::HFONT object )
    {
        return (Font::Handle(object, &::destroy));
    }

    Font::Handle Font::proxy ( ::HFONT object )
    {
        return (Font::Handle(object, &::abandon));
    }

    const Font Font::system ()
    {
        return (Font(claim(::load(SYSTEM_FONT))));
    }

    const Font Font::monospace ()
    {
        return (Font(claim(::load(ANSI_FIXED_FONT))));
    }

    const Font Font::proportional ()
    {
        return (Font(claim(::load(ANSI_VAR_FONT))));
    }

    const Font Font::device ()
    {
        return (Font(claim(::load(DEVICE_DEFAULT_FONT))));
    }

    const Font Font::oem ()
    {
        return (Font(claim(::load(OEM_FIXED_FONT))));
    }

    const Font Font::iconTitle ()
    {
        Attributes attributes;
        const ::BOOL result = ::SystemParametersInfo(
            SPI_GETICONTITLELOGFONT,
            sizeof(Attributes::Data),
            &attributes.data(), 0
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SystemParametersInfo, error);
        }
        return (Font(attributes));
    }

    Font::Font ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Font::Font ( const Attributes& attributes )
        : myHandle(claim(::create(attributes.data())))
    {
    }

    const Font::Handle& Font::handle () const
    {
        return (myHandle);
    }

    void Font::apply ( const Attributes& attributes )
    {
    }

    Font::Attributes::Attributes ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Font::Attributes::Attributes ( const Font& font )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        const int result = ::GetObjectW(font.handle(), sizeof(myData), &myData);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(GetObject, error);
        }
    }

    Font::Attributes::Data& Font::Attributes::data ()
    {
        return (myData);
    }

    const Font::Attributes::Data& Font::Attributes::data () const
    {
        return (myData);
    }

    string Font::Attributes::face () const
    {
        return (myData.lfFaceName);
    }

    void Font::Attributes::face ( const string& face )
    {
        ::wcsncpy(myData.lfFaceName, face.data(), LF_FACESIZE);
    }

    long Font::Attributes::height () const
    {
        return (myData.lfHeight);
    }

    void Font::Attributes::height ( long height )
    {
        myData.lfHeight = height;
    }

    long Font::Attributes::width () const
    {
        return (myData.lfWidth);
    }

    void Font::Attributes::width ( long width )
    {
        myData.lfWidth = width;
    }

    long Font::Attributes::weight () const
    {
        return (myData.lfWeight);
    }

    void Font::Attributes::weight ( long weight )
    {
        myData.lfWeight = weight;
    }

} }
