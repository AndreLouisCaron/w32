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

#include <w32/app/console-program.hpp>

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

#include <w32/app/console-program.cpp>
