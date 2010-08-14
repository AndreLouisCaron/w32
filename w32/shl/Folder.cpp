// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Folder.hpp>
#include <w32/shl/Item.hpp>

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

}

namespace w32 { namespace shl {

    Folder::Folder ( ::IShellFolder * object )
        : com::Wrapper< ::IShellFolder >(object)
    {
    }

    Folder::Folder ( const Item& item )
        : com::Wrapper< ::IShellFolder >( ::cast(item.ptr().value()) )
    {
    }

} }
