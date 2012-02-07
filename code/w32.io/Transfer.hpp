#ifndef _w32_io_Transfer_hpp__
#define _w32_io_Transfer_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32.io/Transfer.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace io {

    class InputStream;

    /*!
     * @ingroup w32-io
     */
    class Transfer :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::OVERLAPPED Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Transfer ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void clear ();

        bool done () const;

        dword finish ( InputStream stream );
    };

} }

#endif /* _w32_io_Transfer_hpp__ */
