// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Storage.hpp>
#include <w32/shl/Folder.hpp>
#include <w32/shl/Item.hpp>
#include <w32/shl/Path.hpp>
#include <w32/shl/Stat.hpp>
#include <w32/shl/Stream.hpp>

namespace {

    ::IStorage * child ( ::IShellFolder * folder, const ::ITEMIDLIST * path )
    {
        const w32::com::Guid I = w32::com::guidof< ::IStorage >();
        ::IStorage * storage = 0;
        const w32::com::Result result = folder->BindToStorage
            (path, 0, I, (void**)&storage);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, BindToStorage, result);
        }
        return (storage);
    }

    ::IStorage * cast ( const w32::shl::Item& item )
    {
        const w32::shl::Folder parent(item.parent());
        const w32::shl::Path name = parent.path(item.name());
        return (child(parent.ptr().value(), name.backend()));
    }

    ::IEnumSTATSTG * enumerate ( ::IStorage * storage )
    {
        ::IEnumSTATSTG * listing = 0;
        const w32::com::Result result =
            storage->EnumElements(0, 0, 0, &listing);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, EnumElements, result);
        }
        return (listing);
    }

}

namespace w32 { namespace shl {

    Storage::Storage ( ::IStorage * object )
        : com::Wrapper< ::IStorage >(object)
    {
    }

    Storage::Storage ( const Item& item )
        : com::Wrapper< ::IStorage >( ::cast(item) )
    {
    }

    Storage::Storage ( const Folder& folder, const Path& path )
        : com::Wrapper< ::IStorage >
              ( ::child(folder.ptr().value(), path.backend()) )
    {
    }

    Stream Storage::open ( const string& child ) const
    {
        const ::DWORD mode = STGM_READ|STGM_SHARE_DENY_WRITE;
        const w32::com::Guid I = w32::com::guidof< ::IStream >();
        ::IStream * stream = 0;
        const w32::com::Result result = ptr()->OpenStream
            (child.data(), 0, mode, 0, &stream);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IStorage, OpenStream, result);
        }
        return (Stream(com::Ptr< ::IStream >(stream)));
    }

    Storage::Listing::Listing ( ::IEnumSTATSTG * object )
        : com::Wrapper< ::IEnumSTATSTG >(object)
    {
    }

    Storage::Listing::Listing ( const Storage& storage )
        : com::Wrapper< ::IEnumSTATSTG >( ::enumerate(storage.ptr().value()) )
    {
    }

    Storage::Listing Storage::Listing::clone () const
    {
        ::IEnumSTATSTG * clone = 0;
        const com::Result result = ptr()->Clone(&clone);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumSTATSTG, Clone, result);
        }
        return (Listing(clone));
    }

    void Storage::Listing::reset () const
    {
        const com::Result result = ptr()->Reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumSTATSTG, Reset, result);
        }
    }

    void Storage::Listing::skip ( size_type count ) const
    {
        const com::Result result = ptr()->Skip(count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumSTATSTG, Skip, result);
        }
    }

    Stat Storage::Listing::next () const
    {
        Stat item;
        const com::Result result = ptr()->Next(1, &item.data(), 0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumSTATSTG, Next, result);
        }
            // Safety first.
        item.myName = string(item.data().pwcsName);
        if ( item.data().pwcsName != 0 ) {
            com::free(item.data().pwcsName);
            item.data().pwcsName = 0;
        }
        return (item);
    }

} }
