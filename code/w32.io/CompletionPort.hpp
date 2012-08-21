#ifndef _w32_io_CompletionPort_hpp__
#define _w32_io_CompletionPort_hpp__

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

/*!
 * @file w32.io/CompletionPort.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/Timespan.hpp>
#include <w32/types.hpp>
#include <w32.io/Stream.hpp>
#include <w32.io/Transfer.hpp>

namespace w32 { namespace io {

    class Notification;

    /*!
     * @ingroup w32-io
     */
    class CompletionPort :
        public Object
    {
        /* nested types. */
    public:
        typedef dword Size;
        typedef ulongptr Data;

        /* construction. */
    public:
        explicit CompletionPort ( dword threads = 0 );
        CompletionPort ( const Stream& stream, Data data, dword threads = 0 );

        /* methods. */
    public:
        void bind ( ::HANDLE object, Data data );
        void bind ( ::HANDLE object, void * data );
        void bind ( ::SOCKET object, Data data );
        void bind ( ::SOCKET object, void * data );

        void bind ( const Stream& stream, Data data );
        void bind ( const Stream& stream, void * data );
        void next ( Size& bytes, Data& data, Transfer *& transfer );
        bool next ( Size& bytes, Data& data,
                    Transfer *& transfer, Timespan timeout );
        void post ( Size size, Data data, ::OVERLAPPED * transfer );
        void post ( Size size, void * data, ::OVERLAPPED * transfer );
        void post ( Size size, Data data, Transfer * transfer );

        void unblock_consumers ();
        Notification next ();
        Notification next ( Timespan timeout );
        Notification peek ();
    };

} }

#endif /* _w32_io_CompletionPort_hpp__ */
