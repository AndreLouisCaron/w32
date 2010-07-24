#ifndef _w32_msi_ColumnInformation_hpp__
#define _w32_msi_ColumnInformation_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/msi/Record.hpp>
#include <w32/msi/View.hpp>

namespace w32 { namespace msi {

        /*!
         * @brief Extracts information about columns affected by an SQL query.
         */
    class W32_MSI_EXPORT ColumnNames :
        public Record
    {
        /* construction. */
    public:
        ColumnNames ( const View& view );
    };

        /*!
         * @brief Extracts information about columns affected by an SQL query.
         */
    class W32_MSI_EXPORT ColumnTypes :
        public Record
    {
        /* construction. */
    public:
        ColumnTypes ( const View& view );
    };

} }

#endif /* _w32_msi_ColumnInformation_hpp__ */
