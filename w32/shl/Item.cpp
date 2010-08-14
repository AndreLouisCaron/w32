// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Item.hpp>

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

} }
