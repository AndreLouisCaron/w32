#ifndef _w32_msi_Database_hpp__
#define _w32_msi_Database_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/msi/Object.hpp>

// See MsiDatabaseExport()/MsiDatabaseImport() for interaction with
// Text Archive Files.

namespace w32 { namespace msi {

        /*!
         * @brief Wraps an msi object.
         *
         * Installer objects are actually miniature relational databases. Thus,
         * the internal file format is hidden under the hood of a database and
         * is opaque.
         */
    class W32_MSI_EXPORT Database :
        public Object
    {
        /* nested types. */
    public:
        class CreationFailed {};
        class InvalidParameter {};
        class OpeningFailed {};
        class BadPathName {};
        class InvalidHandle {};
        class FunctionFailed {};
        class InvalidTable {};
        class DatatypeMismatch {};

            /*!
             * @brief Enumeration of modes with which we can open msi
             *    databases.
             */
        class W32_MSI_EXPORT Mode
        {
            /* class data. */
        public:
            static const Mode readonly ();
            static const Mode transaction ();
            static const Mode direct ();
            static const Mode create ();
            static const Mode createdirect ();

            /* nested types. */
        public:
            typedef ::LPCWSTR Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
                // For internal use only.
            Mode ( Value value );

            /* methods. */
        public:
            Value value () const;
        };

            /*!
             * @brief Enumeration of the states an msi database can be in.
             */
        class W32_MSI_EXPORT State
        {
            /* class data. */
        public:
            static const State read;
            static const State write;
            static const State error;

            /* nested types. */
        public:
            typedef ::MSIDBSTATE Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
                // For internal use only.
            State ( Value value );

            /* class methods. */
        public:
            static State of ( const Database& database );

            /* methods. */
        public:
            Value value () const;

            /* operators. */
        public:
            bool operator== ( const State& other ) const;
            bool operator!= ( const State& other ) const;
        };

        /* data. */
    private:
        Mode myMode;

        /* construction. */
    public:
        explicit Database ( const Handle& handle );
        Database ( const string& path, const Mode& mode );

        /* methods. */
    public:
            /*!
             * @brief Obtains the mode with which the database was opened.
             */
        Mode mode () const;

            /*!
             * @brief Obtains the current state of the msi.
             *
             * If the handle is invalidated for some reason, this will return
             * \c State::error.
             */
        State state () const;

            /*!
             * @brief Saves all changes since the database was opened.
             */
        void commit ();

        void export_ (
            const char * table, const char * folder, const char * file
            );

        void import (
            const char * folder, const char * file
            );

        void merge ( const Database& other, const char * table );
    };

} }

#endif /* _w32_msi_Database_hpp__ */
