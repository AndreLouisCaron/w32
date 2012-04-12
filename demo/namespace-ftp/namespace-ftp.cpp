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

#include <w32.com.hpp>
#include <w32.shl.ext.hpp>

    // Too lazy, even to re-use!
#include "../ftp-client/ftp.hpp"
#include "../ftp-client/ftp.cpp"

namespace {

    class Extension :
        public w32::shl::ext::Namespace
    {
        /* class data. */
    public:
        static const w32::com::Guid guid;

        /* data. */
    private:
        long myReferenceCount;

        /* construction. */
    public:
        Extension ()
            : myReferenceCount(1)
        {
            w32::gdi::messagebox(L"namespace-ftp", L"inside!");
        }

        /* overrides. */
    public:
            // Allow IPersist to return exported class' identifier.
        virtual w32::com::Guid server () const { return (guid); }

            // Standard COM methods.
        virtual w32::ulong __stdcall AddRef () {
            return (::InterlockedIncrement(&myReferenceCount));
        }
        virtual w32::ulong __stdcall Release ()
        {
            if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
            {
                delete this; return (0);
            }
            return (myReferenceCount);
        }
    };

        // This is the unique identifier used to create objects of our class.
    const w32::com::Guid Extension::guid(
        0x5450A57D,0xF5A6,0x42fC,0x87,0xBD,0x7D,0x0F,0xB1,0x9F,0xE9,0xA7
        ); // {5450A57D-F5A6-42fC-87BD-7D0FB19FE9A7}

        // This is the real type of object exposed by the our dynamic library.
    typedef Extension ExportedClass;

}

    // Compile this as a COM in-process server.
#include <w32/app/in-process-server.cpp>
