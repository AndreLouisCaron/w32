#ifndef _w32_msi_Database_hpp__
#define _w32_msi_Database_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "__configure__.hpp"
#include <w32.msi/Object.hpp>

// See MsiDatabaseExport()/MsiDatabaseImport() for interaction with
// Text Archive Files.

namespace w32 { namespace msi {

    /*!
     * @ingroup w32-msi
     * @brief Wraps an msi object.
     *
     * Installer objects are actually miniature relational databases. Thus,
     * the internal file format is hidden under the hood of a database and
     * is opaque.
     */
    class Database :
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
        class Mode
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
        class State
        {
            /* class data. */
        public:
            static const State read ();
            static const State write ();
            static const State error ();

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
