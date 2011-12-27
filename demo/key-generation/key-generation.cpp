// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.cr.hpp>

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Access the provider.
        w32::cr::Provider provider(w32::cr::Provider::Type::rsafull());
        std::wcout << provider.name() << std::endl;
        std::wcout << provider.container() << std::endl;
        
            // Generate keys!
        /*w32::cr::Key::generate
            (provider, w32::cr::Key::Type::exchange());
        w32::cr::Key::generate
            (provider, w32::cr::Key::Type::signature());*/
        
        w32::cr::Hash hash(provider, w32::cr::Hash::Type::md5());
        hash.put("Hello, world!", 13);
        std::wcout << w32::cr::convert(hash.data()) << std::endl;
        
        const w32::cr::Hash::Type algorithm = w32::cr::Hash::Type::rc2();
        w32::cr::Key sessionkey =
            w32::cr::Key::derive(provider, hash, algorithm);
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
