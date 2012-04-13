#ifndef _w32_sc_hpp__
#define _w32_sc_hpp__

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

namespace w32 {
    namespace sc {}
}

/*!
 * @defgroup w32-mt Service control.
 *
 * A full-blown service application might look like the following:
 * @code
 *  namespace {
 *      
 *      // Custom service events. These are accompanied by a "message-only"
 *      // dynamically-linked library. You may also register a single event
 *      // class with a single string parameter and format all messages
 *      // yourself, but the message-only DLL helps with translations!
 *      class ServiceStartup : public w32::dbg::Event {};
 *      class ServiceShutdown : public w32::dbg::Event {};
 *      class DebuggingError : public w32::dbg::Event {};
 *      
 *      const wchar_t ServiceName[] = L"My 1st C++ Service";
 *      
 *      void __stdcall service ( w32::dword argc, wchar_t ** argv )
 *      try
 *      {
 *          w32::Service::Handler handler;
 *          w32::Service::Status status(ServiceName, handler);
 *          
 *         // Technically speaking, the log name could be different from the
 *         // service name, but it's more intuitive to use the same. Note
 *         // That it is normally part of your installation procedure to
 *         // register the event source under this name...
 *         w32::dbg::Log log(ServiceName);
 *         log.report(ServiceStartup(ServiceName));
 *         
 *         try {
 *             // This is not the only way to write the service's
 *             // "quasi-infinite" loop, but you should check the service
 *             // status on a periodic basis. Your may also write a custom
 *             // handler and fire an event, then WaitForMultipleObjects()
 *             // or anything along those lines.
 *             do {
 *                 ///////////////////////////////
 *                 // YOUR _REAL_ SERVICE CODE. //
 *                 ///////////////////////////////
 *             }
 *              while ( status.running() );
 *         }
 *         // Error with an API call.
 *         catch ( w32::dbg::UncheckedError& error ) {
 *             log.report(DebuggingError(error));
 *         }
 *         // Access violation or division by zero and the like.
 *         catch ( w32::dbg::UncheckedError& error ) {
 *             log.report(DebuggingError(error));
 *         }
 *         // Make sure we catch everything we can.
 *         catch ( ... ) {
 *             log.report(DebuggingError(L"Caught unknown exception!"));
 *         }
 *         
 *         log.report(ServiceShutdown(ServiceName));
 *     }
 *     // Probably failed acquiring the event log. In any case, we can't
 *     // report anything without an event log; just don't crash!
 *     catch ( ... ) {}
 * 
 * }
 * 
 * #include <w32/console-program.hpp>
 * namespace {
 * 
 *     int run ( int argc, wchar_t ** argv )
 *     {
 *         // Could deduce other things to do based on arguments.
 *         // Typically, no args means: run!
 *         
 *         // Ask to switch to service context. This will fail if the
 *         // process is not started by the service control manager!
 *         Database().run(::ServiceName, &::service);
 *     }
 * }
 * #include <w32/console-program.cpp>
 * @endcode
 */

#include <w32.sc/Database.hpp>
#include <w32.sc/Object.hpp>
#include <w32.sc/Service.hpp>

#endif /* _w32_sc_hpp__ */
