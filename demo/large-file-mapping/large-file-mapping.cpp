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
#include <w32.fs.hpp>
#include <w32.io.hpp>
#include <w32.mm.hpp>

namespace {

    const w32::dword kilobyte = 1024;
    const w32::dword megabyte = 1024 * kilobyte;
    const w32::dword gigabyte = 1024 * megabyte;

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Make sure we have an argument to access.
        if ( argc < 2 ) {
            std::cerr << "Input file required!" << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Views **must** by mapped in multiples of this amount!
        const w32::dword page = w32::System().granularity();
        
            // Access the file.
        w32::fs::File file(argv[1], w32::fs::File::Access::i());
        const w32::qword size = file.size();
        
            // Ask the system to map the file into memory.
        w32::mm::Mapping mapping(file, w32::mm::Mapping::Mode::i());
        
            // Iterate over the contents of the file!
        w32::qword cursor = 0;
        do {
                // Map up to a page of memory.
            const w32::dword amount = ((cursor+page) <= size)? page : 0;
            w32::mm::Mapping::View view (mapping, cursor, amount);
            
                // Do something... useful?
            const w32::qword total = cursor + amount;
            std::cout
                << "mapped " << total/megabyte << " MBs so far!"
                << std::endl << std::endl;
        }
        while ( (cursor += page) < size );
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
