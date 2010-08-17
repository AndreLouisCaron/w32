#ifndef _w32_shl_Folder_hpp__
#define _w32_shl_Folder_hpp__

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

    class Item;
    class Path;
    class Stream;

    class W32_SHL_EXPORT Folder :
        public com::Wrapper< ::IShellFolder >
    {
        /* nested types. */
    public:
        class Listing;

        /* construction. */
    public:
        explicit Folder ( ::IShellFolder * object );
        explicit Folder ( com::Ptr< ::IShellFolder > object );
        explicit Folder ( const Item& item );
        explicit Folder ( const Folder& parent, const Path& name );

        /* methods. */
    public:
        Stream open ( const Path& path ) const;
        Path path ( const string& item ) const;
        Item child ( const Path& path ) const;
    };

    class W32_SHL_EXPORT Folder::Listing :
        public com::Wrapper< ::IEnumIDList >
    {
        /* nested types. */
    public:
        typedef ulong size_type;

        /* construction. */
    public:
        explicit Listing ( ::IEnumIDList * object );
        Listing ( const Folder& folder );

        /* methods. */
    public:
        Listing clone () const;
        void reset () const;
        bool next ( Path& next );
        void skip ( size_type count ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder > ()
{
    return (IID_IShellFolder);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IEnumIDList > ()
{
    return (IID_IEnumIDList);
}

#endif /* _w32_shl_Folder_hpp__ */
