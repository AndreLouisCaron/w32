#ifndef _w32_msi_View_hpp__
#define _w32_msi_View_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/msi/Database.hpp>
#include <w32/msi/Object.hpp>

// Calling semantics of MsiViewClose() are weird. Check that out.

namespace w32 { namespace msi {

        /*!
         * @brief Wraps an SQL query to an msi database.
         */
    class View :
        public Object
    {
        /* nested types. */
    public:
        class BadSqlSyntax {};
        class FunctionFailed {};
        class InvalidHandle {};
        class InvalidState {};
        class InvalidParameter {};
        class NoMoreRecords {};

        class Column
        {
            /* class data. */
        public:
            static const Column names ();
            static const Column types ();

            /* nested types. */
        public:
            typedef ::MSICOLINFO Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            Column ( Value value );

            /* methods. */
        public:
            Value value () const;
        };

        /* construction. */
    public:
        explicit View ( const Handle& handle );
        View ( const Database& database, const string& query );

        /* methods. */
    public:
        void execute ();
        void close ();
    };

} }

#endif /* _w32_msi_View_hpp__ */
