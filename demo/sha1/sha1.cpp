// Copyright(c) Andre Caron, 2009-2012
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
        w32::cr::Provider::Hints hints;
        hints
            .silent()
            .verifyContext();
        const w32::cr::Provider provider
            (w32::cr::Provider::Type::rsafull(), hints);

        w32::cr::Hash hash = w32::cr::sha1(provider, "", 0);
        std::wcout << w32::cr::convert(hash.data()) << std::endl;

        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
