#ifndef _w32_rgs_Key_hpp__
#define _w32_rgs_Key_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32.rgs/Access.hpp>

namespace w32 { namespace rgs {

        /*!
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
