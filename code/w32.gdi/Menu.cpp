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

#include <w32.gdi/Menu.hpp>
#include <w32/Error.hpp>
#include <string.h>
#include <iostream>

namespace {

    ::HMENU load ( ::HMODULE module, ::LPCWSTR name )
    {
        const ::HMENU handle = ::LoadMenuW(module, name);
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(LoadMenu,::GetLastError());
        }
        return (handle);
    }

    ::HMENU popup ()
    {
        const ::HMENU handle = ::CreatePopupMenu();
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreatePopupMenu,::GetLastError());
        }
        return (handle);
    }

    ::HMENU create ()
    {
        const ::HMENU handle = ::CreateMenu();
        if ( handle == 0 ) {
            UNCHECKED_WIN32C_ERROR(CreateMenu,::GetLastError());
        }
        return (handle);
    }

    void destroy ( ::HMENU object )
    {
        const ::BOOL result = ::DestroyMenu(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

    void abandon ( ::HMENU object )
    {
    }

}

namespace w32 { namespace gdi {

    Menu::Handle Menu::claim ( ::HMENU object )
    {
        return (Menu::Handle(object, &::destroy));
    }

    Menu::Handle Menu::proxy ( ::HMENU object )
    {
        return (Menu::Handle(object, &::abandon));
    }

    Menu Menu::popup ()
    {
        return (Menu(claim(::popup())));
    }

    Menu::Menu ( const Handle& handle )
        : myHandle(handle)
    {
    }

    Menu::Menu ( const Resource& resource )
        : myHandle(::load(
              resource.module().handle(), resource.identifier()
              ))
    {
    }

    Menu::Menu ()
        : myHandle(claim(::create()))
    {
    }

    const Menu::Handle& Menu::handle () const
    {
        return (myHandle);
    }

    uint Menu::popup ( const Window& window, const Point& point )
    {
        const ::BOOL result = ::TrackPopupMenuEx(
            handle(), TPM_NONOTIFY|TPM_RETURNCMD,
            point.x(), point.y(), window.handle(), 0
            );
        return (result);
    }

    void Menu::insert ( const Item& item, uint position )
    {
        const ::BOOL result = ::InsertMenuItemW(
            handle(), position, TRUE, &item.data()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(InsertMenuItem,::GetLastError());
        }
    }

    void Menu::insert ( const string& item, uint position, uint identifier )
    {
        const ::BOOL result = ::InsertMenuW(
            handle(), position, MF_STRING|MF_BYPOSITION,
            identifier, item.data()
            );
        if ( result == FALSE ) {
            UNCHECKED_WIN32C_ERROR(InsertMenu,::GetLastError());
        }
    }

    Menu::Item::Item ( uint identifier )
    {
        ::ZeroMemory(&myData,sizeof(myData));
        myData.cbSize = sizeof(myData);
        myData.wID = identifier;
        myData.fMask |= MIIM_ID;
    }

    const Menu::Item::Data& Menu::Item::data () const
    {
        return (myData);
    }

    void Menu::Item::identifier ( uint identifier )
    {
        myData.wID = identifier;
        myData.fMask |= MIIM_ID;
    }

    void Menu::Item::text ( const string& text )
    {
        myData.fMask = MIIM_STRING;
        myData.dwTypeData = const_cast< ::LPWSTR >(text.data());
        myData.cch = text.length();
    }

} }
