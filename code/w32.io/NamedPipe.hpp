#ifndef _w32_io_NamedPipe_hpp__
#define _w32_io_NamedPipe_hpp__

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
 * @file w32.io/NamedPipe.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 *
 * @brief Pseudo-socket with a UNC name used for inter-process communication.
 */

#include "__configure__.hpp"
#include <w32/string.hpp>
#include <w32.io/Channel.hpp>
#include <w32.io/Transfer.hpp>

namespace w32 { namespace io {

    /*!
     * @ingroup w32-io
     * @brief Full duplex communication channel for local IPC.
     */
    class NamedPipe :
        public Channel
    {
        /* class methods. */
    public:
        /*!
         * @brief Create a named pipe with @a name and buffer @a size.
         */
        static NamedPipe create
            ( const string& name, dword size, bool async=false );

        /*!
         * @brief Wait indefinitely for the pipe with @a name.
         */
        static void wait ( const string& name );

        /*!
         * @brief Wait up to @a timeout milliseconds for the pipe with @a name.
         */
        static bool wait ( const string& name, dword timeout );

        /* construction. */
    public:
        /*!
         * @brief Wrap an existing named pipe handle.
         */
        explicit NamedPipe ( const Handle& handle );

        /*!
         * @brief Opens a named pipe (attempts connection).
         */
        NamedPipe ( const string& name, bool async=false );

        /* methods. */
    public:
        /*!
         * @brief Wait indefinitely for connection request.
         */
        void connect ();

        /*!
         * @brief Request nofication for connection request.
         */
        void connect ( Transfer& transfer );
    };

} }

#endif /* _w32_io_NamedPipe_hpp__ */
