#ifndef _w32_net_Context_hpp__
#define _w32_net_Context_hpp__

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
#include <w32/astring.hpp>
#include <w32/types.hpp>
#include <w32/NotCopyable.hpp>

namespace w32 { namespace net {

    /*!
     * @ingroup w32-net
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
