// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.hpp>
#include <w32.ipc.hpp>
#include <w32.mm.hpp>

namespace {

    w32::pointer modulebase
        ( const w32::ipc::Process& process, const w32::string& name )
    {
            // List modules loaded in that process.
        w32::ipc::Modules modules(process);
        w32::ipc::Modules::Entry module;
        if ( modules.find(module) )
        {
            do {
                    // If a module's name matches, return its base address.
                if ( ::_wcsicmp(module.name().data(), name.data()) == 0 ) {
                    return (module.base());
                }
            }
            while ( modules.next(module) );
        }
            // Sorry, didn't find it.
        return (0);
    }

    template<typename T>
    void copy
        ( void * data, std::size_t size, const T& thing, std::size_t limit )
    {
        ::memcpy(data, &thing, (limit < size)? limit : size);
    }

    template<typename T>
    void copy ( void * data, std::size_t size, const T& thing )
    {
        copy(data, size, thing, sizeof(thing));
    }

}

#include <w32/console-program.hpp>

namespace {

    int run ( int argc, wchar_t ** argv )
    {
            // Determine path to library which should be injected.
        const ::WCHAR path[] = 
            L"C:/Users/ACaron/Desktop/remote-modules/Debug/injectable-dll.dll";
        
            // Choose some process to list modules from.
        w32::ipc::Process process =
            w32::ipc::Process(5100);
            //w32::ipc::Process::current();
        
            // Acquire transfer buffers.
        w32::mm::Heap heap;
        const w32::size_t size = 4*1024;
        const w32::pointer data = heap.acquire(size);
        const w32::pointer base = process.acquire(size);
        
            // Inject library.
        w32::pointer entry = reinterpret_cast<w32::pointer>(&::LoadLibraryW);
        ::copy(data, size, path, 2*::wcslen(path)+2);
        process.put(base, data, size);
        process.call(entry, base).join();
        
            // Recover handle for injected module.
        const w32::pointer file = ::modulebase(process, L"injectable-dll.dll");
        if ( file == 0 ) {
            std::cerr << "Could not find module." << std::endl;
            return (EXIT_FAILURE);
        }
        
            // Run injected DLL function(s).
        do {
                // Prepare.
            entry = process.symbol(file, "_GetCwd@4");
            ::copy(data, size, ::DWORD(size));
            process.put(base, data, size);
                // Execute.
            { w32::mt::Thread call = process.call(entry, base);
                call.join(); process.get(base, data, size);
            }
            std::wcout
                << "Data: '" << ::LPCWSTR(data) << "'."
                << std::endl;
        }
            // Repeat as necessary.
        while ( 0 );
        
            // Eject library.
        if ( true )
        {
                // Prepare.
            entry = process.symbol(file, "_Unload@4");
            ::copy(data, size, file);
            process.put(base, data, size);
                // Execute.
            process.call(entry, base).join();
        }
        
            // Release transfer buffers.
        process.release(base);
        heap.release(data, size);
        
        return (EXIT_SUCCESS);
    }

}

#include <w32/console-program.cpp>

    // Link automagically.
#pragma comment ( lib, "w32.lib" )
#pragma comment ( lib, "w32.dbg.lib" )
#pragma comment ( lib, "w32.ipc.lib" )
#pragma comment ( lib, "w32.mm.lib" )
#pragma comment ( lib, "w32.mt.lib" )
