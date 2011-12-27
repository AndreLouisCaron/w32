// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/app/console-program.hpp>
#include <w32.msi.hpp>

namespace {

    int run ( int, wchar_t ** )
    try
    {
        w32::msi::Products products(
            w32::msi::Products::User::current(),
            w32::msi::Products::Context::unmanaged()
            );
        while ( products.next() )
        {
            w32::msi::Product product(products.current());
            std::wcout
                << product.code() << std::endl
                << product(INSTALLPROPERTY_PRODUCTNAME) << std::endl
                << product(INSTALLPROPERTY_LANGUAGE) << std::endl
                << product(INSTALLPROPERTY_VERSION) << std::endl
                << std::endl;
        }
        
        return (EXIT_SUCCESS);
    }
    catch ( const w32::msi::Error& error ) {
        std::cerr << error.what() << std::endl << std::endl;
        return (EXIT_FAILURE);
    }

}

#include <w32/app/console-program.cpp>
