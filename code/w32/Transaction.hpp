#ifndef _w32_Transaction_hpp__
#define _w32_Transaction_hpp__

// Copyright(c) Andre Caron, 2009-2012
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32/Transaction.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     */
    class Transaction :
        public Object
    {
        /* nested types. */
    public:
            // Wrapper is in com::Guid!
        //typedef ::GUID Identifier;

        /* construction. */
    public:
            // Create a new transaction.
        Transaction ();
        Transaction ( const string& description );

            // Open an existing transaction.
        //Transaction ( const Identifier& identifier );

        /* methods. */
    public:
        void commit ();
        void rollback ();
    };

}

#endif /* _w32_Transaction_hpp__ */
