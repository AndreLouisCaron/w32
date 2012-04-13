#ifndef _w32_Codepage_hpp__
#define _w32_Codepage_hpp__

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

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Character set for byte strings.
     * @see astring
     *
     * A character encoding is a mapping of numeric identifiers to specific
     * characters. Many such mappings exist.
     *
     * @note Although the Unicode Transformation Formats (UTF) are technically
     * character encodings, text data in UTF-16 is not usually considered
     * "encoded".  This is due to the fact that it is the most complete
     * character representation and can be (possibly lossyly) encoded into any
     * other encoding.
     */
    class Codepage
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation for enumerated values.
         */
        typedef uint Value;

        /* class data. */
    public:
        /*!
         * @brief ANSI/ASCII codepage.
         */
        static const Codepage ansi ();

        /*!
         * @brief Original Equipment Manufacturer OEM codepage.
         *
         * This encoding is primarily used for MS-DOS console input/output.
         */
        static const Codepage oem ();

        /*!
         * @brief Unicode Transformation Format for 7-bit clean channels.
         */
        static const Codepage utf7 ();

        /*!
         * @brief Unicode Transformation Format for exchange and storage.
         */
        static const Codepage utf8 ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        // For internal use only.
        Codepage ( Value value );

        /* methods. */
    public:
        /*!
         * @return The native representation for the enumeration.
         */
        Value value () const;

        /*!
         * @return @c true if the code page number is valid.
         */
        bool valid () const;

        /* operators. */
    public:
        /*!
         * @return The native representation for the enumeration.
         */
        operator Value () const;

        /*!
         * @return @c true if @c *this holds the same value as @a rhs does.
         */
        bool operator== ( const Codepage& ) const;

        /*!
         * @return @c false if @c *this holds the same value as @a rhs does.
         */
        bool operator!= ( const Codepage& ) const;
    };

}

#endif /* _w32_Codepage_hpp__ */
