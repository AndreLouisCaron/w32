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
#include <w32.cr.hpp>

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
        // Access the provider.
        w32::cr::Provider::Hints hints;
        hints
            .silent()
            .verifyContext();
        w32::cr::Provider provider(w32::cr::Provider::Type::rsafull(), hints);
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
