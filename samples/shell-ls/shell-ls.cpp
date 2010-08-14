// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.com.hpp>
#include <w32.shl.hpp>

namespace w32 { namespace shl {

} }

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Get a hold of the current directory.
        const w32::shl::Path path =
            w32::currentdirectory();
        const w32::shl::Item item = path;
        
            // Print a list of its siblings' names.
        const w32::shl::Folder folder(item.parent());
        const w32::shl::Listing listing(folder);
        do {
            const w32::shl::Item child = listing.next();
            std::wcout << child.name() << std::endl;
        }
        while ( true );
        
        return (0);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.com.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.shl.lib" )
