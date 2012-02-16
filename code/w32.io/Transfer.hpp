#ifndef _w32_io_Transfer_hpp__
#define _w32_io_Transfer_hpp__

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
 * @file w32.io/Transfer.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>

namespace w32 { namespace io {

    class InputStream;

    /*!
     * @ingroup w32-io
     */
    class Transfer :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::OVERLAPPED Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Transfer ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void clear ();

        bool done () const;

        dword finish ( InputStream stream );
    };

} }

#endif /* _w32_io_Transfer_hpp__ */
