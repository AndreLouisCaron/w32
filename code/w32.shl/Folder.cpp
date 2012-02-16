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

#include <w32.shl/Folder.hpp>
#include <w32.shl/Binding.hpp>
#include <w32.shl/Item.hpp>
#include <w32.shl/Path.hpp>
#include <w32.shl/Stream.hpp>
#include <w32/string.hpp>
#include <w32/Variant.hpp>

namespace {

    ::IShellFolder * cast ( ::IShellItem * item )
    {
        const w32::com::Guid I = w32::com::guidof< ::IShellFolder >();
        ::IShellFolder * folder = 0;
        const w32::com::Result result =
            item->BindToHandler(0, BHID_SFObject, I, (void**)&folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, BindToHandler, result);
        }
        return (folder);
    }

    ::IShellFolder * open
        ( ::IShellFolder * parent, ::LPCITEMIDLIST path )
    {
        const w32::com::Guid& I = w32::com::guidof< ::IShellFolder >();
        ::IShellFolder * folder = 0;
        const w32::com::Result result =
            parent->BindToObject(path, 0, I, (void**)&folder);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, BindToObject, result);
        }
        return (folder);
    }

    ::IEnumIDList * create ( ::IShellFolder * folder )
    {
        const ::DWORD flags = SHCONTF_FOLDERS  | SHCONTF_NONFOLDERS;
        ::IEnumIDList * listing = 0;
        const w32::com::Result result =
            folder->EnumObjects(0, flags, &listing);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, EnumObjects, result);
        }
        return (listing);
    }

}

namespace w32 { namespace shl {

    Folder::Folder ( ::IShellFolder * object )
        : com::Wrapper< ::IShellFolder >(object)
    {
    }

    Folder::Folder ( com::Ptr< ::IShellFolder > object )
        : com::Wrapper< ::IShellFolder >(object)
    {
    }

    Folder::Folder ( const Item& item )
        : com::Wrapper< ::IShellFolder >( ::cast(item.ptr().value()) )
    {
    }

    Folder::Folder ( const Folder& parent, const Path& name )
        : com::Wrapper< ::IShellFolder >
              ( ::open(parent.ptr().value(), name.backend()) )
    {
    }

    Stream Folder::open ( const Path& path ) const
    {
            // Ask for object in readonly mode.
        w32::shl::Binding binding;
        w32::shl::Binding::Options options = binding.options();
        options.access(STGM_READ|STGM_SHARE_DENY_WRITE);
        binding.options(options);
        
            // Open it.
        const w32::com::Guid I = w32::com::guidof< ::IStream >();
        ::IStream * stream = 0;
        const w32::com::Result result = ptr()->BindToStorage
            (path.backend(), binding.ptr().value(), I, (void**)&stream);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, BindToObject, result);
        }
        return (Stream(com::Ptr< ::IStream >(stream)));
    }

    Path Folder::path ( const string& item ) const
    {
        ::ULONG eaten = 0;
        ::ULONG attributes = 0;
        ::ITEMIDLIST * path = 0;
        wchar_t *const name = const_cast< wchar_t*>(item.data());
        const com::Result result = ptr()->ParseDisplayName
            (0, 0, name, &eaten, &path, &attributes);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, ParseDisplayName, result);
        }
        return (Path::box(path));
    }

    Item Folder::child ( const Path& path ) const
    {
        return (Item(*this, path));
    }

    Folder2::Folder2 ( ::IShellFolder2 * object )
        : com::Wrapper< ::IShellFolder2 >(object)
    {
    }

    Folder2::Folder2 ( const Folder& folder )
        : com::Wrapper< ::IShellFolder2 >
              ( com::cast< ::IShellFolder2 >(folder.ptr().value()) )
    {
    }

    qword Folder2::size ( const Path& path ) const
    {
        const ::GUID storage = {0xB725F130, 0x47EF, 0x101A,
            0xA5, 0xF1, 0x02, 0x60, 0x8C, 0x9E, 0xEB, 0xAC};
        const ::SHCOLUMNID column = {storage, 12};
        
        Variant size;
        const com::Result result = ptr()->GetDetailsEx
            (path.backend(), &column, &size.value());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, GetDetailsEx, result);
        }
        return (size);
    }

    Folder::Listing::Listing ( ::IEnumIDList * object )
        : com::Wrapper< ::IEnumIDList >(object)
    {
    }

    Folder::Listing::Listing ( const Folder& folder )
        : com::Wrapper< ::IEnumIDList >( ::create(folder.ptr().value()) )
    {
    }

    Folder::Listing Folder::Listing::clone () const
    {
        ::IEnumIDList * clone = 0;
        const com::Result result = ptr()->Clone(&clone);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Clone, result);
        }
        return (Listing(clone));
    }

    void Folder::Listing::reset () const
    {
        const com::Result result = ptr()->Reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Reset, result);
        }
    }

    void Folder::Listing::skip ( size_type count ) const
    {
        const com::Result result = ptr()->Skip(count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Skip, result);
        }
    }

    bool Folder::Listing::next ( Path& next )
    {
        ::ITEMIDLIST * item = 0;
        const com::Result result = ptr()->Next(1, &item, 0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Next, result);
        }
        if ( result != w32::com::Result::false_() ) {
            next = Path(item);
            com::free(item);
            return (true);
        }
        return (false);
    }

} }
