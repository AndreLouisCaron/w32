#ifndef _w32_rgs_Access_hpp__
#define _w32_rgs_Access_hpp__

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

namespace w32 { namespace rgs {

    /*!
     * @ingroup w32-rgs
     * @brief Enumerates access types for registry keys.
     *
     * Key access restrictions are applied on a per-handle basis, and only when
     * opening an existing key.  The system may refuse access to certain keys
     * for security reasons.  For instance, write access to
     * @c HKEY_LOCAL_MACHINE is not granted unless the process is running with
     * elevated priviledges.  If you only want to determine if a certain product
     * is installed, you may probably enumerate @c HKEY_LOCAL_MACHINE\SOFTWARE
     * by requesting access using @c w32::rgs::Access::read() only.
     *
     * @note The access is given when opening a registry key and only
     *  defines the access the given handle will allow you (i.e. this is
     *  not persistent).
     */
    class Access
    {
        /* nested types. */
    public:
        /*!
         * @brief Native access mask representation.
         */
        typedef ::REGSAM Value;

        /* class data. */
    public:
        /*! @brief Permission to enumerate sub-keys and values. */
        static const Access list ();

        /*! @brief Permission to read values. */
        static const Access get ();

        /*! @brief Permission to add, change and remove values. */
        static const Access set ();

        /*! @brief Permission to create and delete sub-keys. */
        static const Access create ();

        /*! @brief @c list()|get(). */
        static const Access read ();

        /*! @brief @c set()|create(). */
        static const Access write ();

        /*! @brief @c read()|write(), default for newly created keys. */
        static const Access all ();

        /* members. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        Access ( Value value );

        /* methods. */
    public:
        /*!
         * @brief Returns the native representation for the enumeration.
         */
        Value value () const;

        /* operators. */
    public:
        /*!
         * @brief Combine with another access mode.
         */
        Access& operator|= ( const Access& other );

        /*!
         * @brief Combine with another access mode.
         */
        Access operator| ( const Access& other ) const;

        /*!
         * @brief Exclude another access mode.
         */
        Access& operator&= ( const Access& other );

        /*!
         * @brief Exclude another access mode.
         */
        Access operator& ( const Access& other ) const;

        /*!
         * @brief Returns the native representation for the enumeration.
         */
        operator Value () const;
    };

} }

#endif /* _w32_rgs_Access_hpp__ */
