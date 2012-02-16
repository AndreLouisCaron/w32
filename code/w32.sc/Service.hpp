#ifndef _w32_sc_Service_hpp__
#define _w32_sc_Service_hpp__

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
#include <w32/string.hpp>
#include <w32.sc/Object.hpp>

namespace w32 { namespace sc {

    class Database;

    class Service :
        public Object
    {
        /* nested types. */
    public:
        typedef void ( __stdcall * Context )( dword argc, wchar_t** argv );

        class Status;
        class Handler;

        /* construction. */
    public:
        Service (
            Database& database, const string& name, const string& path
            );

        Service ( Database& database, const string& name );

        /* methods. */
    public:
        void remove ();
    };

    class Service::Status
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
        static const Status stopped;
        static const Status starting;
        static const Status stopping;
        static const Status running;
        static const Status resuming;
        static const Status pausing;
        static const Status paused;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Status ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const Status& other ) const;
        bool operator!= ( const Status& other ) const;
    };

    class Service::Handler :
        private NotCopyable
    {
        /* members. */
    private:
        ::SERVICE_STATUS_HANDLE myHandle;
        ::SERVICE_STATUS myValue;

        /* construction. */
    public:
        Handler ( const string &service );
        ~Handler ();

        /* methods. */
    public:
        void signal () const volatile;
        void signal ( const Status& status ) volatile;
        Status current () const volatile;
        void exit ( dword code ) volatile;

            // Serve a double purpose... change this!
        virtual void stop () volatile;
        virtual void pause () volatile;
        virtual void resume () volatile;
        virtual void control ( int code ) volatile;
    };

} }

#endif /* _w32_sc_Service_hpp__ */
