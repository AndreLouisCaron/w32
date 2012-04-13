#ifndef _w32_Architecture_hpp__
#define _w32_Architecture_hpp__

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

    class System;

    /*!
     * @ingroup w32
     * @brief Enumeration of hardware architecture family.
     */
    class Architecture
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation of the enumeration values.
         */
        typedef word Value;

        /* class data. */
    public:
        /*! @brief 64-bit AMD architecture, new 64-bit Intel architecture. */
        static const Architecture x64 ();

        /*! @brief Old 64-bit Intel architecture (Itanium family). */
        static const Architecture ia64 ();

        /*! @brief 32-bit Intel architecture. */
        static const Architecture x86 ();

        /*! @brief Placeholder for any unknown hardware architecture. */
        static const Architecture unknown ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        // For internal use only.
        Architecture ( Value value );

        /* class methods. */
    public:
        /*!
         * @brief Extract @a system's architecture.
         * @see System::architecture()
         */
        static Architecture of ( const System& system );

        /* methods. */
    public:
        /*!
         * @return The native representation for the enumeration.
         */
        Value value () const;

        /* operators. */
    public:
        /*!
         * @return The native representation for the enumeration.
         */
        operator Value() const;

        /*!
         * @return @c true if @c *this holds the same value as @a rhs does.
         */
        bool operator== ( const Architecture& other ) const;

        /*!
         * @return @c false if @c *this holds the same value as @a rhs does.
         */
        bool operator!= ( const Architecture& other ) const;
    };

}

#endif /* _w32_Architecture_hpp__ */
