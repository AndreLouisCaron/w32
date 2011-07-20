// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Item.hpp>
#include <w32/shl/Attributes.hpp>
#include <w32/shl/Folder.hpp>
#include <w32/shl/Location.hpp>
#include <w32/shl/Path.hpp>
#include <ntquery.h>

namespace {

    ::IShellItem * open ( const ::ITEMIDLIST * path )
    {
        ::IShellItem * item = 0;
        const w32::com::Result result =
            ::SHCreateShellItem(0, 0, path, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, SHCreateShellItem, result);
        }
        return (item);
    }

    ::IShellItem * open ( ::IShellFolder * parent, const ::ITEMIDLIST * path )
    {
        ::IShellItem * item = 0;
        const w32::com::Result result =
            ::SHCreateShellItem(0, parent, path, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, SHCreateShellItem, result);
        }
        return (item);
    }

}

namespace w32 { namespace shl {

    Item::Item ( ::IShellItem * object )
        : com::Wrapper< ::IShellItem >(object)
    {
    }

    Item::Item ( const Path& path )
        : com::Wrapper< ::IShellItem >( ::open(path.backend()) )
    {
    }

    Item::Item ( const Folder& parent, const Path& path )
        : com::Wrapper< ::IShellItem >(
              ::open(parent.ptr().value(), path.backend()) )
    {
    }

    Item Item::parent () const
    {
        ::IShellItem * parent = 0;
        const com::Result result = ptr()->GetParent(&parent);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetParent, result);
        }
        return (Item(parent));
    }

    string Item::name () const
    {
        const ::SIGDN format = SIGDN_NORMALDISPLAY;
        wchar_t * name = 0;
        const com::Result result = ptr()->GetDisplayName(format, &name);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetDisplayName, result);
        }
        const string value(name);
        //com::free(name);
        return (value);
    }

    Attributes Item::attributes () const
    {
        return (attributes(Attributes::all()));
    }

    Attributes Item::attributes ( Attributes mask ) const
    {
        return (Attributes::of(*this, mask));
    }

    int Item::compare ( const Item& rhs ) const
    {
        const ::SICHINTF hint = SICHINT_ALLFIELDS;
        int order = 0;
        const com::Result result =
            ptr()->Compare(rhs.ptr().value(), hint, &order);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, Compare, result);
        }
        return (order);
    }

    bool Item::operator== ( const Item& rhs ) const
    {
        return (this->compare(rhs) == 0);
    }

    bool Item::operator!= ( const Item& rhs ) const
    {
        return (this->compare(rhs) != 0);
    }

    Item root ()
    {
        return (Location::desktop());
    }

    Path abspath ( const Item& item )
    {
        const Item parent = item.parent();
        const Folder folder(parent);
        const string name = item.name();
        try {
            const Path last = folder.path(name);
            return (Path(abspath(parent), folder.path(name)));
        }
            // todo: stop on something better than an exception!
        catch ( ... ) {}
        return (Path());
    }

    Item2::Item2 ( ::IShellItem2 * object )
        : com::Wrapper< ::IShellItem2 >(object)
    {
    }

    Item2::Item2 ( const Item& item )
        : com::Wrapper< ::IShellItem2 >
              ( com::cast< ::IShellItem2 >(item.ptr().value()) )
    {
    }

    qword Item2::size () const
    {
        const ::GUID storage = { 0xB725F130, 0x47EF, 0x101A,
            0xA5, 0xF1, 0x02, 0x60, 0x8C, 0x9E, 0xEB, 0xAC};
        const ::SHCOLUMNID PKEY_Size = {storage, PID_STG_SIZE};
        ::ULONGLONG size = 0;
        const com::Result result = ptr()->GetUInt64(PKEY_Size, &size);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem2, GetUInt64, result);
        }
        return (size);
    }

} }
