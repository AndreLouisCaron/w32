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

#include <w32.com.hpp>
#include <w32.shl.hpp>
#include <iomanip>
#include <iostream>

#include <w32/app/console-program.hpp>

namespace {

    const w32::com::Guid SERVER(
        0x5450A57D,0xF5A6,0x42fC,0x87,0xBD,0x7D,0x0F,0xB1,0x9F,0xE9,0xA7
        ); // {5450A57D-F5A6-42fC-87BD-7D0FB19FE9A7}

    const w32::string FILE = "C:\\Users\\André\\Desktop\\foo.ftp";

    int run ( int argc, wchar_t ** argv )
    try
    {
    const w32::com::Library _;
        
#if 0
        w32::shl::Attributes attributes;
        attributes |= w32::shl::Attributes::browsable();
        attributes |= w32::shl::Attributes::folder();
        attributes |= w32::shl::Attributes::subfolders();
        attributes |= w32::shl::Attributes::container();
        std::cout << std::setw(8) << std::hex
            << attributes.value() << std::endl;
#endif
        
            // Load the extension as an IShellFolder.
        const w32::shl::Folder root(
            w32::com::instantiate< ::IShellFolder >(SERVER));
        
            // Tell the IShellFolder where it's at.
        const w32::shl::Path path = FILE;
        const w32::com::Ptr< ::IPersistFolder > persist =
            w32::com::cast< ::IPersistFolder >(root.ptr());
        persist->Initialize(path.backend());
        
            // Request folder contents.
        w32::shl::Folder::Listing listing(root);
        for ( w32::shl::Path item; listing.next(item); )
        {
            std::wcout << L"  >> " << (w32::string)item << std::endl;
        }
        
        return (EXIT_SUCCESS);
    }
    catch ( w32::com::Error& error )
    {
        std::cerr << error.what() << std::endl;
        return (EXIT_FAILURE);
    }
}

#include <w32/app/console-program.cpp>

template<> inline w32::com::Guid
    w32::com::guidof< ::IPersistFolder > ()
{
    return (IID_IPersistFolder);
}
