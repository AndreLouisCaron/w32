#ifndef _w32_rgs_Type_hpp__
#define _w32_rgs_Type_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 { namespace rgs {

    class Value;

        /*!
         * @brief Enumerates all types of value we can store under a registry key.
         */
    class W32_RGS_EXPORT Type
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
            /*! @brief The value stores no data. */
        static const Type none ();

            /*! @brief Null-terminated string. This is the most common type of value. */
        static const Type string ();

            /*! @brief Double-word (32-bit unsigned integer). */
        static const Type dword ();

            /*! @brief Binary data.
             *
             * @note If the data is large, you should consider writing the data to a file and
             *   storing only the path to that file as a string instead.
             */
        static const Type binary ();

            /*!
             * @brief Null-terminated string with expandable environment variables.
             *
             * The strings are not automatically expanded when their values are retrieved. This is
             * mainly a flag to client applications that they should expand the variables when they
             * use them. A common use for this is to store a relative path to the user's profile
             * or the application data folder, etc.
             */
        static const Type unexpanded ();

            /*!
             * @brief Double null-terminated list of null-terminated strings.
             */
        static const Type multistring ();

        /* class methods. */
    public:
        static const Type of ( const rgs::Value& value );

        /* data. */
    private:
        Value myValue;

        /* construction.*/
    private:
        Type ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const Type& other ) const;
        bool operator!= ( const Type& other ) const;

        operator Value () const;
    };

} }

#endif /* _w32_rgs_Type_hpp__ */
