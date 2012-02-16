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

#include <w32.gdi/OpenGLContext.hpp>
#include <w32.gdi/DeviceContext.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HGLRC current ()
    {
        return (::wglGetCurrentContext());
    }

    ::HDC device ()
    {
        return (::wglGetCurrentDC());
    }

    ::HGLRC create ( ::HDC device )
    {
        const ::HGLRC handle = ::wglCreateContext(device);
        if ( handle == 0 ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(wglCreateContext, error);
        }
        return (handle);
    }

    void destroy ( ::HGLRC object )
    {
        const ::BOOL result = ::wglDeleteContext(object);
        if ( result == FALSE ) {
            w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HGLRC object )
    {
    }

}

namespace w32 { namespace gdi {

    OpenGLContext::Handle OpenGLContext::claim ( ::HGLRC object )
    {
        return (Handle(object, &::destroy));
    }

    OpenGLContext::Handle OpenGLContext::proxy ( ::HGLRC object )
    {
        return (Handle(object, &::abandon));
    }

    OpenGLContext OpenGLContext::current ()
    {
        return (OpenGLContext(proxy(::current())));
    }

    OpenGLContext::OpenGLContext ( const Handle& handle )
        : myHandle(handle)
    {
    }

    OpenGLContext::OpenGLContext ( const DeviceContext& device )
        : myHandle(claim(::create(device.handle())))
    {
    }

    const OpenGLContext::Handle& OpenGLContext::handle () const
    {
        return (myHandle);
    }

    OpenGLContext::Use::Use ( DeviceContext& device, OpenGLContext& context )
        : myPreviousDevice(::wglGetCurrentDC()),
          myPreviousContext(::wglGetCurrentContext())
    {
        const ::BOOL result = ::wglMakeCurrent(
            device.handle(), context.handle());
        if ( result == FALSE ) {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(wglMakeCurrent, error);
        }
    }

    OpenGLContext::Use::~Use ()
    {
            // Be a nice citizen :-)
        ::wglMakeCurrent(myPreviousDevice, myPreviousContext);
    }

} }
