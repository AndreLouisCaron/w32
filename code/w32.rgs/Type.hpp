#ifndef _w32_rgs_Type_hpp__
#define _w32_rgs_Type_hpp__

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
#include <w32/types.hpp>

namespace w32 { namespace rgs {

    class Value;

    /*!
     * @ingroup w32-rgs
     * @brief Enumerates all types of value we can store under a registry key.
     */
    class Type
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
