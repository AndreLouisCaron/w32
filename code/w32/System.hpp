#ifndef _w32_System_hpp__
#define _w32_System_hpp__

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
#include <w32/Architecture.hpp>
#include <w32/types.hpp>

namespace w32 {

    /*!
     * @ingroup w32
     * @brief Information about the operating system's hardware architecture.
     */
    class System
    {
        /* nested types. */
    public:
        /*!
         * @brief Native representation.
         */
        typedef ::SYSTEM_INFO Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        /*!
         * @brief Obtains information about the runing system.
         */
        System ();

        /* methods. */
    public:
        /*!
         * @brief Read-write access to the native structure.
         */
        Data& data ();

        /*!
         * @brie Read-only access to the native structure.
         */
        const Data& data () const;

        /*!
         * @brief Obtains the system's hardware architecture.
         */
        Architecture architecture () const;

        /*!
         * @brief Obtains the size of memory pages.
         */
        dword pagesize () const;

        /*!
         * @brief Obtains the number of CPU cores on the system.
         */
        dword processors () const;

        /*!
         * @brief The granularity for virtual memory base addresses.
         */
        dword granularity () const;
    };

}

#endif /* _w32_System_hpp__ */
