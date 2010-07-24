// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Icon.hpp>
#include <w32/Error.hpp>
#include <iostream>

namespace {

    ::HICON load ( ::LPCWSTR path )
    {
        const ::HICON handle = (::HICON)::LoadImageW(
            0, path, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadImage, error);
        }
        return (handle);
    }

    ::HICON load
        ( ::HMODULE module, ::LPCWSTR name, int cx, int cy, ::UINT flags )
    {
        const ::HANDLE handle = ::LoadImageW(
            module, name, IMAGE_ICON, cx, cy, flags
            );
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadImage, error);
        }
        return (reinterpret_cast< ::HICON >(handle));
    }

    ::HICON fetch ( ::LPSTR icon )
    {
        const ::HICON handle = ::LoadIcon(0, icon);
        if ( handle == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LoadIcon, error);
        }
        return (handle);
    }

    void destroy ( ::HICON object )
    {
        if ( ::DestroyIcon(object) == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HICON object )
    {
    }

}

namespace w32 { namespace gdi {

    const Icon Icon::none ()
    {
        return (Icon(proxy(0)));
    }

    const Icon Icon::application ()
    {
        return (Icon(proxy(::fetch(IDI_APPLICATION))));
    }

    const Icon Icon::asterisk ()
    {
        return (Icon(proxy(::fetch(IDI_ASTERISK))));
    }

    const Icon Icon::error ()
    {
        return (Icon(proxy(::fetch(IDI_ERROR))));
    }

    const Icon Icon::exclamation ()
    {
        return (Icon(proxy(::fetch(IDI_EXCLAMATION))));
    }

    const Icon Icon::hand ()
    {
        return (Icon(proxy(::fetch(IDI_HAND))));
    }

    const Icon Icon::information ()
    {
        return (Icon(proxy(::fetch(IDI_INFORMATION))));
    }

    const Icon Icon::question ()
    {
        return (Icon(proxy(::fetch(IDI_QUESTION))));
    }

    const Icon Icon::warning ()
    {
        return (Icon(proxy(::fetch(IDI_WARNING))));
    }

    const Icon Icon::winlogo ()
    {
        return (Icon(proxy(::fetch(IDI_WINLOGO))));
    }

    Icon::Handle Icon::claim ( ::HICON object )
    {
        return (Icon::Handle(object, &destroy));
    }

    Icon::Handle Icon::proxy ( ::HICON object )
    {
        return (Icon::Handle(object, &abandon));
    }

    Icon::Icon ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Icon::Icon ( const string& path )
        : myHandle(claim(::load(path.c_str())))
    {
    }

    Icon::Icon ( const Resource& resource )
        : myHandle(claim(::load(
              resource.module().handle(), resource.identifier(),
              0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED
              )))
    {
    }

    Icon::Icon ( const Resource& resource, const Size& size )
        : myHandle(claim(::load(
            resource.module().handle(), resource.identifier(),
            size.value().width(), size.value().height(),
            LR_DEFAULTCOLOR | LR_SHARED
            )))
    {
    }

    Icon::Icon (
        const Resource& resource, const w32::gdi::Size& size
        )
        : myHandle(claim(::load(
            resource.module().handle(), resource.identifier(),
            size.width(), size.height(), LR_DEFAULTCOLOR | LR_SHARED
            )))
    {
    }

    const Icon::Handle& Icon::handle () const
    {
        return (myHandle);
    }

    const Icon::Size Icon::Size::big ()
    {
        return (Size(Value(32,32)));
    }

    const Icon::Size Icon::Size::small ()
    {
        return (Size(Value(16,16)));
    }

    Icon::Size::Size ( const Value& size )
        : mySize(size)
    {
    }

    const Icon::Size::Value& Icon::Size::value () const
    {
        return (mySize);
    }

} }
