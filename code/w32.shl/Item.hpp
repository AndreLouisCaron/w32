#ifndef _w32_shl_Item_hpp__
#define _w32_shl_Item_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32.com/Wrapper.hpp>

namespace w32 { namespace shl {

    class Attributes;
    class Folder;
    class Path;

    class Item :
        public com::Wrapper< ::IShellItem >
    {
        /* construction. */
    public:
        explicit Item ( ::IShellItem * object );
        Item ( const Path& path );
        Item ( const Folder& folder, const Path& path );

        /* methods. */
    public:
        Item parent () const;
        string name () const;
        Attributes attributes () const;
        Attributes attributes ( Attributes mask ) const;
        int compare ( const Item& rhs ) const;

        /* operators. */
    public:
        bool operator== ( const Item& rhs ) const;
        bool operator!= ( const Item& rhs ) const;
    };

    Item root ();

    Path abspath ( const Item& item );

    class Item2 :
        public com::Wrapper< ::IShellItem2 >
    {
        /* construction. */
    public:
        explicit Item2 ( ::IShellItem2 * object );
        Item2 ( const Item& item );

        /* methods. */
    public:
        qword size () const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellItem > ()
{
    return (IID_IShellItem);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellItem2 > ()
{
    return (IID_IShellItem2);
}

#endif /* _w32_shl_Item_hpp__ */
