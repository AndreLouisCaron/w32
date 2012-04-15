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


#include "Stopwatch.hpp"
#include <w32/Delta.hpp>
#include <w32/Error.hpp>

#include <iostream>

namespace {

    w32::int64 read_counter ()
    {
        ::LARGE_INTEGER counter;
        const ::BOOL status = ::QueryPerformanceCounter(&counter);
        if (status == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(QueryPerformanceCounter, error);
        }
        return (counter.QuadPart);
    }

    w32::Delta make_delta
        ( w32::int64 frequency, w32::int64 reference, w32::int64 now )
    {
        const double delta =
            double(now-reference) / double(frequency);
        return (w32::Delta::second()*delta);
    }

}

namespace w32 { namespace dbg {

    Stopwatch::Stopwatch ()
    {
        // Determine what the counter frequency is and fix the units.
        ::LARGE_INTEGER frequency;
        const ::BOOL status = ::QueryPerformanceFrequency(&frequency);
        if (status == FALSE)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(QueryPerformanceFrequency, error);
        }
        myFrequency = frequency.QuadPart;

        // Establish the reference time to the time of creation.
        myReference = ::read_counter();
    }

    Delta Stopwatch::reset ()
    {
        // Fetch the current time.
        const int64 now = ::read_counter();

        // Compute the time delta.
        const Delta delta = ::make_delta(myFrequency, myReference, now);

        // Update the reference time.
        myReference = now;

        return (delta);
    }

    Delta Stopwatch::read () const
    {
        // Fetch the current time.
        const int64 now = ::read_counter();

        // Compute the time delta.
        return (::make_delta(myFrequency, myReference, now));
    }

} }
