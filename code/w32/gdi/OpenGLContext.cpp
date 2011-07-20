// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/OpenGLContext.hpp>
#include <w32/gdi/DeviceContext.hpp>
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
