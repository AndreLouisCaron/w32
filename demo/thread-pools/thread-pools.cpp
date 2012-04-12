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
#include <w32.mt.hpp>
#include <w32.tp.hpp>

namespace {

    void foo ( w32::tp::Hints&, void * context )
    {
        std::cout << "foo(0x" << context << ")" << std::endl;
    }

    void bar ( w32::tp::Hints&, void * context )
    {
        std::cout << "bar(0x" << context << ")" << std::endl;
    }

    void __stdcall meh ( void * object, void * cleanup )
    {
        std::cout << "meh(0x" << object
            << ",0x" << cleanup << ")" << std::endl;
    }

}

#include <w32/app/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Create a thread pool and associated work queue.
        w32::tp::Pool pool; pool.threads(1);
        w32::tp::Queue queue(pool);
        
            // Dummy context.
        int a = 0; int b = 1; int c = 2;
        std::cout << "&a = 0x" << &a << std::endl;
        std::cout << "&b = 0x" << &b << std::endl;
        std::cout << "&c = 0x" << &c << std::endl;
        
            // Queue jobs.
        w32::tp::Timer foo(queue, w32::tp::Timer::function<&::foo>(), &a); 
        w32::tp::Timer bar(queue, w32::tp::Timer::function<&::bar>(), &b);
        foo.start(2000);
        bar.start(5000);
        
            // Wait for 'foo()' to finish, but not 'bar()'.
        w32::mt::sleep(w32::Timespan(4000));
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
