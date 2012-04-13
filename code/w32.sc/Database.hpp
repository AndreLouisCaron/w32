#ifndef _w32_sc_Database_hpp__
#define _w32_sc_Database_hpp__

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
#include <w32.sc/Service.hpp>
#include <w32/types.hpp>
#include <w32/string.hpp>

namespace w32 { namespace sc {

    /*!
     * @brief Utility used to install, run and delete service programs.
     *
     * The service control manager is the mechanism used by the operating
     * system to allow you to manage service programs. Service programs
     * are virtual extensions to the operating system. These programs
     * perform background work in a set-it-and-forget-it fashion: you
     * install one, configure it and basically never deal with it again
     * unless you want to delete the program. It can be configure to
     * start automatically after you computer boots up and shutdown before
     * your OS does (the usual case).
     */
    class Database :
        public Object
    {
        /* construction. */
    public:
        /*!
         * @brief Open a connection to the SCM on the local machine.
         *
         * This gives you all-access rights to the service control manager,
         * including installation, execution and removal of services.  This
         * may require the user executing the program to have system
         * administrative privilidges.
         */
        Database ();

        /* methods. */
    public:
        /*!
         * @brief Executes the service.
         * @param service Name of the service.
         * @param context User-supplied main function for the service.
         *
         * This function can only be executed from inside a process that was
         * started by the SCM (it must be a service process).  @a service is
         * the name displayed in the SCM's user interface.
         */
        void run ( const string& service, Service::Context context );
    };

} }

#endif /* _w32_sc_Database_hpp__ */
