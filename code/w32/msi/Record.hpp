#ifndef _w32_msi_Record_hpp__
#define _w32_msi_Record_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/msi/Object.hpp>
#include <w32/msi/View.hpp>

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
