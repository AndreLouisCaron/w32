#ifndef _w32_shl_Storage_hpp__
#define _w32_shl_Storage_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Wrapper.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace shl {

    class Folder;
    class Item;
    class Path;
    class Stat;
    class Stream;

    class W32_SHL_EXPORT Storage :
        public com::Wrapper< ::IStorage >
    {
        /* nested types. */
    public:
        class Listing;

        /* construction. */
    public:
        explicit Storage ( ::IStorage * object );
        explicit Storage ( const Item& item );
        Storage ( const Folder& folder, const Path& path );

        /* methods. */
    public:
        Stream open ( const string& child ) const;
    };

    class W32_SHL_EXPORT Storage::Listing :
        public com::Wrapper< ::IEnumSTATSTG >
    {
        /* nested types. */
    public:
        typedef ulong size_type;

        /* construction. */
    public:
        explicit Listing ( ::IEnumSTATSTG * object );
        Listing ( const Storage& storage );

        /* methods. */
    public:
        Listing clone () const;
        void reset () const;
        Stat next () const;
        void skip ( size_type count ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IStorage > ()
{
    return (IID_IStorage);
}

#endif /* _w32_shl_Storage_hpp__ */
