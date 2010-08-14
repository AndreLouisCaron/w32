// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Listing.hpp>
#include <w32/shl/Item.hpp>

namespace {

    ::IEnumShellItems * create ( ::IShellItem * item )
    {
        const w32::com::Guid& I = w32::com::guidof< ::IEnumShellItems >();
        ::IEnumShellItems * listing = 0;
        const w32::com::Result result =
            item->BindToHandler(0, BHID_StorageEnum, I, (void**)&listing);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, BindToHandler, result);
        }
        return (listing);
    }

}

namespace w32 { namespace shl {

    Listing::Listing ( ::IEnumShellItems * object )
        : com::Wrapper< ::IEnumShellItems >(object)
    {
    }

    Listing::Listing ( const Item& item )
        : com::Wrapper< ::IEnumShellItems >( ::create(item.ptr().value()) )
    {
    }

    Listing Listing::clone () const
    {
        ::IEnumShellItems * clone = 0;
        const com::Result result = ptr()->Clone(&clone);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Clone, result);
        }
        return (Listing(clone));
    }

    void Listing::reset () const
    {
        const com::Result result = ptr()->Reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Reset, result);
        }
    }

    void Listing::skip ( size_type count ) const
    {
        const com::Result result = ptr()->Skip(count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Skip, result);
        }
    }

    bool Listing::next ( Item& next )
    {
        ::IShellItem * item = 0;
        const com::Result result = ptr()->Next(1, &item, 0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Next, result);
        }
        if ( result == w32::com::Result::false_() ) {
            return (false);
        }
        next = Item(item);
        return (true);
    }

} }
