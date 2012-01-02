#ifndef _w32_net_Buffer_hpp__
#define _w32_net_Buffer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace net {

    /*!
     * @ingroup w32-net
     */
    class Buffer :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::WSABUF Data;
        typedef ::ULONG size_type;
        typedef ::CHAR value_type;
        typedef value_type * iterator;
        typedef const value_type * const_iterator;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Buffer ();
        Buffer ( iterator begin, size_type size );
        Buffer ( iterator begin, iterator end );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        iterator begin (); const_iterator begin () const;
        iterator   end (); const_iterator   end () const;
    };

} }

#endif /* _w32_net_Buffer_hpp__ */
