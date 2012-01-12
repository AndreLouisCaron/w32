#ifndef _w32_io_NamedPipe_hpp__
#define _w32_io_NamedPipe_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
