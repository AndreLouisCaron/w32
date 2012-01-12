#ifndef _w32_io_CompletionPort_hpp__
#define _w32_io_CompletionPort_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/CompletionPort.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/Timespan.hpp>
#include <w32/types.hpp>
#include <w32.io/Stream.hpp>
#include <w32.io/Transfer.hpp>

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     */
    class CompletionPort :
        public Object
    {
        /* nested types. */
    public:
        typedef dword Size;
        typedef ulongptr Key;

        /* construction. */
    public:
        explicit CompletionPort ( dword threads = 0 );
        CompletionPort ( const Stream& stream, Key key, dword threads = 0 );

        /* methods. */
    public:
        void bind ( const Stream& stream, Key key );
        void bind ( const Stream& stream, void * key );
        void get ( Size& bytes, Key& key, Transfer *& transfer );
        bool get ( Size& bytes, Key& key, Transfer *& transfer, Timespan timeout );
        void put ( Size bytes, Key key, Transfer * transfer );
    };

} }

#endif /* _w32_io_CompletionPort_hpp__ */
