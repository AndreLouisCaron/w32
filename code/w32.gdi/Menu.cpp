// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
