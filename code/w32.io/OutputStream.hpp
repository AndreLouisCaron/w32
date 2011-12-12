#ifndef _w32_io_OutputStream_hpp__
#define _w32_io_OutputStream_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32.io/Stream.hpp>

namespace w32 { namespace io {

     class OutputStream :
         public Stream
     {
         /* construction. */
     public:
         explicit OutputStream ( const Handle& handle );

         /* methods. */
     public:
            /*!
             * @param buffer Pointer to the first free character in the buffer.
             * @param bytes Number of bytes in the buffer.
             *
             * @return The number of characters successfully written.
             */
         dword put ( const byte * buffer, dword bytes );
     };

} }

#endif /* _w32_io_OutputStream_hpp__ */