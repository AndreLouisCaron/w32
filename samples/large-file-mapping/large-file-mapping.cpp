// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.fs.hpp>
#include <w32.io.hpp>
#include <w32.mm.hpp>

namespace {

    const w32::dword kilobyte = 1024;
    const w32::dword megabyte = 1024 * kilobyte;
    const w32::dword gigabyte = 1024 * megabyte;

}

#include <w32/console-program.hpp>

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

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.fs.lib" )
#pragma comment ( lib, "w32.io.lib" )
#pragma comment ( lib, "w32.mm.lib" )
