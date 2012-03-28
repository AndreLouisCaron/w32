#ifndef _echo_Task_hpp__
#define _echo_Task_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "../Task.hpp"
#include "../Buffer.hpp"

namespace echo {

    class Service;

    class Task :
        public server::Task
    {
        /* data. */
    private:
        w32::net::tcp::Stream myStream;

        server::IBuffer myGBuf;
        server::OBuffer myPBuf;

        /* construction. */
    public:
        Task ( Service& service, w32::net::tcp::Stream& stream );

        /* overrides. */
    public:
        virtual void acquired ();
        virtual void released ();

        virtual bool done () const;
        virtual void abort ();
        virtual void completed
            ( const w32::io::Transfer * transfer, w32::dword size );
    };

}

#endif /* _echo_Task_hpp__ */
