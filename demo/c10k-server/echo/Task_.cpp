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
