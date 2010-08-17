#ifndef _w32_shl_Listing_hpp__
#define _w32_shl_Listing_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace shl {

    class Item;

    class W32_SHL_EXPORT Listing :
        public com::Wrapper< ::IEnumShellItems >
    {
        /* nested types. */
    public:
        typedef ulong size_type;

        /* construction. */
    public:
        explicit Listing ( ::IEnumShellItems * object );
        Listing ( const Item& item );

        /* methods. */
    public:
        Listing clone () const;
        void reset () const;
        bool next ( Item& next );
        void skip ( size_type count ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IEnumShellItems > ()
{
    return (IID_IEnumShellItems);
}

#endif /* _w32_shl_Listing_hpp__ */
