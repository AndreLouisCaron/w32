#ifndef _w32_dbg_Log_hpp__
#define _w32_dbg_Log_hpp__

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
#include <w32.dbg/Event.hpp>

namespace w32 { namespace dbg {

    /*!
     * @brief Persistant, standard, localizable, logging mechanism.
     *
     * @note In order to be used properly, the event log needs to be registered
     *  when the application is installed (don't forget to unregister it when
     *  uninstalling, your users will appreciate it :-).
     */
    class Log
    {
        /* nested types. */
    public:
        typedef Reference< ::HANDLE, void(*)(::HANDLE) > Handle;

        /* class methods. */
    public:
        /*!
         * @brief Creates a handle that will eventually release @a object.
         */
        static Handle claim ( ::HANDLE object );

        /*!
         * @brief Creates a handle that will never release @a object.
         */
        static Handle proxy ( ::HANDLE object );

        /*!
         * @brief Register an event log.
         * @param name Name of the event source to install.
         * @param path path to the message-only DLL containing string
         *  resources.
         * @param categories path to the resource-only DLL containing
         *  application-defined message category definitions.
         * @param count numer of application-defined message categories.
         *
         * @see remove()
         */
        static void install (
            const string& name, const string& path,
            const string& categories, dword count );

        /*!
         * @brief Unregister an event log.
         * @param name Name of the event source to uninstall.
         * @see install()
         */
        static void remove ( const string& name );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        /*!
         * @brief Wrap an existing event log handle.
         */
        explicit Log ( const Handle& handle );

        /*!
         * @brief Opens an application event log.
         * @param name Application event log name.
         */
        Log ( const string& name );

        /* methods. */
    public:
        /*!
         * @return The event log's handle.
         */
        const Handle& handle () const;

        /*!
         * @brief Report an event to the application's event log.
         * @param event Event to store in the persistent event log.
         */
        void report ( const Event& event );
    };

} }

#endif /* _w32_dbg_Log_hpp__ */
