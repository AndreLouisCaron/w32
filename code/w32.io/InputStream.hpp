#ifndef _w32_io_InputStream_hpp__
#define _w32_io_InputStream_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/InputStream.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32.io/Stream.hpp>

namespace w32 {

    class Waitable;

}

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     */
    class InputStream :
        public Stream
    {
        /* construction. */
    public:
        explicit InputStream ( const Handle& handle );

        /* methods. */
    public:
           /*!
            * @param buffer Pointer to the first free character in the buffer.
            * @param bytes Number of bytes in the buffer.
            *
            * @return The number of characters successfully read.
            */
        dword get ( byte * buffer, dword bytes );

        /* operators. */
    public:
        operator w32::Waitable () const;
    };

} }

#endif /* _w32_io_InputStream_hpp__ */
