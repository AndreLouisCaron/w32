#ifndef _w32_ipc_Modules_hpp__
#define _w32_ipc_Modules_hpp__

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

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/Object.hpp>
#include <w32/types.hpp>
#include <w32.ipc/Process.hpp>

namespace w32 { namespace ipc {

    /*!
     * @ingroup w32-ipc
     * @brief Enumerate all modules loaded into a process.
     */
    class Modules :
        public Object
    {
        /* nested types. */
    public:
        class Entry;

        /* construction. */
    public:
        Modules ( Process::Identifier process );
        Modules ( const Process& process );

        /* methods. */
    public:
        bool find ( Entry& entry );
        bool next ( Entry& entry );
    };

    class Modules::Entry
    {
        /* nested types. */
    public:
        typedef ::MODULEENTRY32W Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Entry ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void clear ();

        const pointer base () const;
        const string name () const;
        const string path () const;
    };

} }

#endif /* _w32_ipc_Modules_hpp__ */
