// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.mt.hpp>

namespace {

    void foo ()
    {
        std::cout << "foo()" << std::endl;
    }

    void bar ( void * context )
    {
        std::cout << "bar(0x" << context << ")" << std::endl;
        
            // Re-schedule indefinitely.
        /*w32::mt::Queue& queue = *static_cast<w32::mt::Queue*>(context);
        const w32::Timespan bardelai( 250);
        queue.submit(w32::mt::Queue::adapt<void*,&bar>(), bardelai, &queue);*/
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
        w32::mt::Pool pool; pool.threads(1);
        w32::mt::Queue queue; queue.pool(pool);
        
            // Pretty please, with sugar on top, clean the fucking car.
        w32::mt::Cleanup cleanup;
        //queue.cleanup(cleanup, &::meh);
        
            // Dummy context.
        int a = 0; int b = 1; int c = 2;
        std::cout << "&a = 0x" << &a << std::endl;
        std::cout << "&b = 0x" << &b << std::endl;
        
            // Queue jobs.
        const w32::Timespan foodelai(2000);
        const w32::Timespan bardelai( 250);
        queue.submit(w32::mt::Queue::adapt<void ,&::foo>(), foodelai, &a);
        queue.submit(w32::mt::Queue::adapt<void*,&::bar>(), bardelai, &queue);
        
            // Wait for 'foo()' to finish, but not 'bar()'.
        w32::mt::sleep(w32::Timespan(3000));
        
            // Pretty please, with sugar on top, clean the fucking car.
        cleanup.close(true, &c);
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/app/console-program.cpp>
