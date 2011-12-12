// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.net.hpp>
#include <w32.hpp>
#include <algorithm>
#include <iostream>

namespace {

    void print ( const wchar_t * value )
    {
        std::wcout << "Alias: " << value << std::endl;
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
     const w32::net::Context _;
        
        w32::string name = w32::computername();
        if ( argc > 1 ) {
            name = argv[1];
        }
        w32::net::Host host(name);
        //std::cout << host.name() << std::endl;
        w32::net::Host::Aliases aliases(host);
        std::for_each(aliases.begin(),aliases.end(),&print);
        const std::size_t count = host.addresses();
        for ( std::size_t i = 0; (i < count); ++i )
        {
            std::cout
                << "IPv6: " << host.address<w32::net::ipv6::Address>(i)
                << std::endl;
        }
        return (0);
    }

}

#include <w32/app/console-program.cpp>
