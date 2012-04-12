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
#include <w32.rgs.hpp>
#include <w32.shl.hpp>
#include <sstream>

namespace {

    void explore ( const w32::shl::Item& item );

    void extension ( const w32::shl::Item& item )
    try
    {
        std::wcout
            << L"(( exploring: " << item.name() << L" ))" << std::endl;
        
            // Get the item's absolute path.
        const w32::shl::Path path = w32::shl::abspath(item);
        
            // Ask Windows' implementation to load the extension for us.
        const w32::shl::Item root = w32::shl::root();
        w32::shl::Folder folder(w32::shl::Folder(root), path);
        std::cout << "  -- opened!" << std::endl;
        
            // Get a a listing...
        w32::shl::Folder::Listing listing(folder);
        std::cout << "  -- listed!" << std::endl;
        for ( w32::shl::Path name; listing.next(name); )
        {
            w32::shl::Item child = folder.child(name);
            std::wcout << L"    >> " << child.name() << L":";
            const w32::shl::Attributes attributes = child.attributes();
            if ( attributes & w32::shl::Attributes::folder() )
            {
                    // Apply scheme recursively!
                explore(child);
            }
            else if ( attributes & w32::shl::Attributes::stream() )
            {
                w32::shl::Stream contents = folder.open(name);
                
                    // Show proof of proper access!
                char buffer[6];
                buffer[contents.read(buffer, sizeof(buffer)-1)] = '\0';
                std::cout.write(buffer, sizeof(buffer)) << std::endl;
            }
        }
        std::cout << " -- finished!" << std::endl;
    }
    catch ( const w32::com::Error& error )
    {
        std::cout << error.what() << std::endl;
        std::cout << " -- finished!" << std::endl;
    }

    void explore ( const w32::shl::Item& item )
    try
    {
            // Handle namespace extensions as a special case!
        if ( item.attributes() & w32::shl::Attributes::stream() ) {
            extension(item); return;
        }
        
        std::wcout
            << L"(( exploring: " << item.name() << L" ))" << std::endl;
        
        const w32::shl::Folder parent(item.parent());
        const w32::shl::Folder folder(parent, parent.path(item.name()));
        std::cout << "  -- opened!" << std::endl;
        w32::shl::Listing listing(item);
        std::cout << "  -- listed!" << std::endl;
        
            // Access each child stream's contents.
        const w32::shl::Storage storage(item);
        for ( w32::shl::Item child(0); listing.next(child); )
        {
            std::wcout << L"    >> " << child.name() << L":";
            const w32::shl::Attributes attributes = child.attributes();
            if ( attributes & w32::shl::Attributes::folder() )
            {
                    // Apply scheme recursively!
                explore(child);
            }
            else if ( attributes & w32::shl::Attributes::stream() )
            {
                w32::shl::Stream contents = storage.open(child.name());
                
                    // Show proof of proper access!
                char buffer[6];
                buffer[contents.read(buffer, sizeof(buffer)-1)] = '\0';
                std::cout.write(buffer, sizeof(buffer)) << std::endl;
            }
        }
        std::cout << " -- finished!" << std::endl;
    }
    catch ( const w32::com::Error& error )
    {
        std::cout << error.what() << std::endl;
        std::cout << " -- finished!" << std::endl;
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    try
    {
            // Uses a lot of COM...
    w32::com::Library _;
        
            // Explore the current working directory.
        ::explore(w32::shl::Item(w32::currentdirectory()));
        
        return (0);
    }
    catch ( const w32::com::Error& error )
    {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/app/console-program.cpp>
