#ifndef _w32_Time_hpp__
#define _w32_Time_hpp__

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

/*!
 * @file w32/Time.hpp
 */

#include "__configure__.hpp"
#include <w32/types.hpp>

namespace w32 {

    class Delta;

    /*!
     * @ingroup w32
     * @brief System time.
     */
    class Time
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation.
         */
        typedef ::SYSTEMTIME Data;

        /* data. */
    private:
        Data myData;

        /* class methods. */
    public:
        /*!
         * @return A snapshot of the current time in the active locale.
         */
        static Time now ();

        /* construction. */
    public:
        /*!
         * @brief Builds a placeholder time object (all zeros).
         */
        Time ();

        /*!
         * @brief Wrap an existing time structure.
         */

        Time ( const Data& value );

        /*!
         * @brief Convert a filesystem time to a system time structure.
         */
        Time ( const ::FILETIME& value );

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

        word year () const;
        word month () const;
        word day () const;
        word hour () const;
        word minute () const;
        word second () const;
        word millisecond () const;

        /* operators. */
    public:
        /*!
         * @brief Apply a time delta.
         */
        Time& operator+= ( const Delta& delta );
    };

    /*!
     * @brief Apply a time delta.
     */
    Time operator+ ( const Time& time, const Delta& delta );

}

#endif /* _w32_Time_hpp__ */
