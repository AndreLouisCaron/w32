// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Task.hpp"
#include "Service.hpp"
#include "../Core.hpp"
#include <algorithm>

namespace echo {

    Task::Task ( Service& service, w32::net::tcp::Stream& stream )
        : server::Task(service), myStream(stream),
          myGBuf(8192,1024), myPBuf(8192,1024)
    {
    }

    bool Task::done () const
    {
        return (false);
    }

    void Task::acquired ()
    {
            // Register for I/O completion notifications.
        core().bind(myStream, *this);
        
            // Initiate first read request.
        myGBuf.get(myStream);
    }

    void Task::released ()
    {
    }

    void Task::abort ()
    {
        myStream.shutdown(w32::net::Socket::Shutdown::both());
    }

    void Task::completed
        ( const w32::io::Transfer * transfer, w32::dword size )
    {
            // Close session upon remote shutdown.
        if ( size == 0 ) {
            core().del(this); return;
        }
        
            // Just received 'size' bytes of data.
        if ( myGBuf.owns(*transfer) )
        {
            std::cout << " >> " << size << " bytes." << std::endl;
            
                // Acknowledge completion.
            myGBuf.did(size);
            
                // Replicate data to client.
            myPBuf << myGBuf;
            
                // Initiate output, request more input!
            myPBuf.put(myStream);
            myGBuf.get(myStream);
        }
            // Just sent 'size' bytes of data.
        if ( myPBuf.owns(*transfer) )
        {
            std::cout << " << " << size << " bytes." << std::endl;
            
                // Acknowledge completion.
            myPBuf.did(size);
        }
    }

}
