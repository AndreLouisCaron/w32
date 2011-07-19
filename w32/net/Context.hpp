#ifndef _w32_net_Context_hpp__
#define _w32_net_Context_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/astring.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>

namespace w32 { namespace net {

        /*!
         * @brief RAII object to initialize the WinSock2 library.
         */
    class Context :
        private NotCopyable
    {
        /* nested types. */
    public:
            /*!
             * @brief Library information returned by the initialization.
             */
        typedef ::WSADATA Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
            /*!
             * @brief Initializes the WinSock2 library.
             *
             * @warning Before this object has been constructed, all the
             *   services in the w32::net namespace must not be used.
             */
        Context ();

            /*!
             * @brief Cleans-up the WinSock2 library.
             *
             * @warning After this object has been destroyed, all the services
             *   in the w32::net namespace should no longer be used.
             */
        ~Context ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the native initialization data.
             */
        Data& data ();

            /*!
             * @brief Obtains the native initialization data.
             */
        const Data& data () const;

            /*!
             * @brief Obtains the library version.
             */
        dword version () const;

        astring description () const;
        astring status () const;
    };

} }

#endif /* _w32_net_Context_hpp__ */
