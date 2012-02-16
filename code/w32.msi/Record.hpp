#ifndef _w32_msi_Record_hpp__
#define _w32_msi_Record_hpp__

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
#include <w32.msi/View.hpp>

namespace w32 { namespace msi {

        /*!
         * @brief Array of fields for an SQL query.
         *
         * This object serves both as means to specify field values in a
         * prepared update and as a means to retrive the values when reading the
         * results of a query.
         */
    class Record :
        public Object
    {
        /* nested types. */
    public:
        class CreationFailed {};
        class InvalidHandle {};
        class NullInteger {};
        class InvalidParameter {};
        class InvalidField {};

        /* data. */
    private:
        ::UINT myField; // deprecated.

        /* construction. */
    public:
            /*!
             * @brief Creates an object used to read results from a query.
             */
        Record ( View& view );

        explicit Record ( ::UINT fields );

    protected:
        explicit Record ( const Handle& handle );

        /* methods. */
    public:
            /*!
             * @brief Indicates if a given field has no value (is null).
             */
        bool null ( ::UINT field ) const;

            /*!
             * @brief Obtains the size of a field.
             *
             * If the field is an integer, the size of an integer, in bytes, is
             * returned; if the field is a string, the number of characters,
             * excluding any terminator, is returned and; if the record is a
             * stream, the number of bytes in the stream is returned.
             */
        uint size ( uint field ) const;

            /*!
             * @brief Obtains the number of fields in the record.
             */
        uint fields () const;

            /*!
             * @brief Empties the values of all fields (sets them all to null).
             */
        void clear ();

        int integer ( uint field ) const;
        string string ( uint field ) const;

        /* operators. */
    private:
            // Field setters... (deprecated).
        Record& operator<< ( int value );
        Record& operator<< ( const std::string& value );
        Record& operator<< ( const std::wstring& value );
    };

} }

#endif /* _w32_msi_Record_hpp__ */
