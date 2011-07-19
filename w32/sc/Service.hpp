#ifndef _w32_sc_Service_hpp__
#define _w32_sc_Service_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
#include <w32/sc/Object.hpp>

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
