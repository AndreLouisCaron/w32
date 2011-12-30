// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
