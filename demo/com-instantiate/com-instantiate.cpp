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

#include <w32.hpp>
#include <w32.com.hpp>
#include <sstream>

namespace {

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    try
    {
    const w32::com::Library _;
        
            // Parse the requested object uuid.
        if ( argc < 2 )
        {
            std::cerr
                << "What object?" << std::endl;
            return (EXIT_FAILURE);
        }
        std::wistringstream input(argv[1]);
        w32::com::Guid guid;
        if ( !(input >> guid) )
        {
            std::cerr
                << "Expecting an object GUID!" << std::endl;
            return (EXIT_FAILURE);
        }
        std::wcerr << guid << std::endl;
        
            // Create an instance of the requested type.
        const w32::com::Ptr< ::IUnknown > instance
            = w32::com::instantiate(guid);
        
        return (EXIT_SUCCESS);
    }
    catch ( const w32::com::Error& error )
    {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/app/console-program.cpp>
