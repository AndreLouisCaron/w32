#ifndef _w32_msi_Columns_hpp__
#define _w32_msi_Columns_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32.msi/Record.hpp>
#include <w32.msi/View.hpp>

namespace w32 { namespace msi {

    /*!
     * @ingroup w32-msi
     * @brief Extracts information about columns affected by an SQL query.
     */
    class Columns :
        public Record
    {
        /* construction. */
    public:
        Columns ( const View& view, const View::Column& information );
    };

} }

#endif /* _w32_msi_Columns_hpp__ */
