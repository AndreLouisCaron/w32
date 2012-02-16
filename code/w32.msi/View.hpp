#ifndef _w32_msi_View_hpp__
#define _w32_msi_View_hpp__

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
#include <w32.msi/Database.hpp>
#include <w32.msi/Object.hpp>

// Calling semantics of MsiViewClose() are weird. Check that out.

namespace w32 { namespace msi {

    /*!
     * @ingroup w32-msi
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
