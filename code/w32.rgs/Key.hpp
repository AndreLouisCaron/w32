#ifndef _w32_rgs_Key_hpp__
#define _w32_rgs_Key_hpp__

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
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32.rgs/Access.hpp>

namespace w32 { namespace rgs {

    /*!
     * @ingroup w32-rgs
     * @brief Allows manipulation of registry keys from different sources.
     */
    class Key
    {
        /* nested types. */
    public:
        typedef Reference< ::HKEY > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HKEY object );
        static Handle proxy ( ::HKEY object );

            /*!
             * @brief Create a new key (doesn't fail if it exists).
             */
        static Key create ( const Key& parent, const string& path );

            /*!
             * @brief Create a new key (doesn't fail if it exists).
             */
        static Key create (
            const Key& parent, const string& path, const string& value
            );

        /* class data. */
    public:
            /*! @brief HKEY_LOCAL_MACHINE. */
        static const Key machine ();

            /*! @brief HKEY_CURRENT_USER. */
        static const Key user ();

            /*! @brief HKEY_USERS. */
        static const Key users ();

            /*! @brief HKEY_CLASSES_ROOT. */
        static const Key classes ();

#   if (_WIN32_WINNT  >= 0x0600)
            /*! @brief HKEY_CURRENT_CONFIG. This is new to Windows Vista. */
        static const Key configuration ();
#   endif

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        explicit Key ( const Handle& handle );

            /*!
             * @brief Open a key and get the requested access right.
             */
        Key (
            const Key& parent, const string& path,
            const Access& access = Access::all()
            );

        /* methods. */
    public:
        const Handle& handle () const;

            /*!
             * @brief Flush the key's data.
             */
        void flush ();

            /*!
             * @brief Remove a value.
             */
        void remove ( const string& value );

            /*!
             * @brief Delete a sub-key.
             */
        void delete_ ( const string& subkey );

        /* operators. */
    public:
            /*!
             * @brief Sets the default value for the key.
             */
        Key& operator= ( const string& value );
    };

} }

#endif /* _w32_rgs_Key_hpp__ */
