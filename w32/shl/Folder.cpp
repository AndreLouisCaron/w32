// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Folder.hpp>
#include <w32/shl/Binding.hpp>
#include <w32/shl/Item.hpp>
#include <w32/shl/Path.hpp>
#include <w32/shl/Stream.hpp>
#include <w32/string.hpp>

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
        ( ::IShellFolder * parent, const ::ITEMIDLIST * path )
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
