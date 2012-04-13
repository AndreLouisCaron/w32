#ifndef _w32_Version_hpp__
#define _w32_Version_hpp__

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
#include <w32/string.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Operating system version.
     */
    class Version
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation.
         */
        typedef ::OSVERSIONINFOEXW Data;

        /* class methods. */
    public:
        /*!
         * @brief Windows 2000.
         */
        static Version _2000 ();

        /*!
         * @brief Windows XP.
         */
        static Version xp ();

        /*!
         * @brief Windows Vista.
         */
        static Version vista ();

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        /*!
         * @brief Get the running system's version.
         */
        Version ();

        /*!
         * @brief Select a specific version.
         *
         * @note The resulting structure is incomplete.  This is normally used
         *  for performing version validation.
         */
        Version ( dword major, dword minor );

        /* methods. */
    public:
        /*!
         * @brief Access the native representation.
         */
        Data& data ();

        /*!
         * @brief Access the native representation.
         */
        const Data& data () const;

        dword major () const;
        dword minor () const;
        dword build () const;

        /* operators. */
    public:
        /*!
         * @return @c true if two versions have the same major and minor
         *  version numbers.
         *
         * @note Build/patch numbers are ignored by comparisons.
         */
        bool operator== ( const Version& rhs ) const;

        /*!
         * @return @c true if @c *this has a lesser major version number or an
         *  equal major version number and a lesser minor version numbers.
         *
         * @note Build/patch numbers are ignored by comparisons.
         */
        bool operator< ( const Version& rhs ) const;
    };

}

#endif /* _w32_Version_hpp__ */
