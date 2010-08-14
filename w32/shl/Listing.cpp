// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Listing.hpp>
#include <w32/shl/Folder.hpp>
#include <w32/shl/Path.hpp>

namespace {

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

    Listing::Listing ( ::IEnumIDList * object )
        : com::Wrapper< ::IEnumIDList >(object)
    {
    }

    Listing::Listing ( const Folder& folder )
        : com::Wrapper< ::IEnumIDList >( ::create(folder.ptr().value()) )
    {
    }

    Listing Listing::clone () const
    {
        ::IEnumIDList * clone = 0;
        const com::Result result = ptr()->Clone(&clone);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Clone, result);
        }
        return (Listing(clone));
    }

    void Listing::reset () const
    {
        const com::Result result = ptr()->Reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Reset, result);
        }
    }

    void Listing::skip ( size_type count ) const
    {
        const com::Result result = ptr()->Skip(count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Skip, result);
        }
    }

    Path Listing::next () const
    {
        ::ITEMIDLIST * item = 0;
        const com::Result result = ptr()->Next(1, &item, 0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumIDList, Next, result);
        }
        //com::free(item);
        return (Path(item));
    }

} }
