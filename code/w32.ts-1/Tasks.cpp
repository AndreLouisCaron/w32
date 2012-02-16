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

#include <w32.ts-1/Tasks.hpp>
#include <w32.ts-1/Scheduler.hpp>
#include <w32/Reference.hpp>

namespace {

    void release ( wchar_t * object )
    {
        ::CoTaskMemFree(object);
    }

    typedef w32::Reference< wchar_t* > Buffer;

    Buffer claim ( wchar_t * object )
    {
        return (Buffer(object, &release));
    }

    ::IEnumWorkItems * create ( ::ITaskScheduler * scheduler )
    {
        ::IEnumWorkItems * enumeration = 0;
        const w32::com::Result result = scheduler->Enum(&enumeration);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskScheduler, Enum, result);
        }
        return (enumeration);
    }

}

namespace w32 { namespace ts {

    Tasks::Tasks ( const Scheduler& scheduler )
        : com::Wrapper< ::IEnumWorkItems >( ::create(scheduler.ptr().value()) )
    {
    }

    bool Tasks::next ( string& name )
    {
        ::LPWSTR * names = 0;
        ::DWORD count = 0;
        const com::Result result = ptr()->Next(1, &names, &count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumWorkItems,Next,result);
        }
        if ( count == 0 ) {
            return (false);
        }
        name = ::claim(names[0]);
        return (true);
    }

} }
