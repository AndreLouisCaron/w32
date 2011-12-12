#ifndef _w32_shl_Stream_hpp__
#define _w32_shl_Stream_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace shl {

    class Item;
    class Path;
    class Stat;

    class Stream :
        public com::Wrapper< ::IStream >
    {
        /* class methods. */
    public:
        static Stream open ( const shl::Path& path );

        /* construction. */
    public:
        explicit Stream ( const Ptr& backend );
        explicit Stream ( const Item& item );

        /* methods. */
    public:
        ulong read ( void * buffer, ulong bytes );
        ulong write ( const void * buffer, ulong bytes );
        void stat ( Stat& info ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IStream > ()
{
    return (IID_IStream);
}


#endif /* _w32_shl_Stream_hpp__ */
