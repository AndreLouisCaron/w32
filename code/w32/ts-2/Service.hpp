#ifndef _w32_ts_Service_hpp__
#define _w32_ts_Service_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

namespace w32 { namespace ts {

        /*!
         * @brief Enhanced task scheduler for Windows Vista.
         */
    class Service :
        public com::Wrapper< ::ITaskService >
    {
        /* construction. */
    public:
            /*!
             * @brief Open a connection to the task scheduler on the local
             *    machine.
             */
        explicit Service ();

        /* methods. */
    public:
            /*!
             * @brief Obtains the name of the server's domain.
             */
        bstring domain () const;

            /*!
             * @brief Obtains the name of the server that hosts the scheduler.
             */
        bstring server () const;

            /*!
             * @brief Obtains the user name used for the connection.
             */
        bstring user () const;
    };

} }

#endif /* _w32_ts_Service_hpp__ */
