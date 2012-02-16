#ifndef _w32_dbg_Log_hpp__
#define _w32_dbg_Log_hpp__

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
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32.dbg/Event.hpp>

namespace w32 { namespace dbg {

    class Log
    {
        /* nested types. */
    public:
        typedef Reference< ::HANDLE, void(*)(::HANDLE) > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::HANDLE object );
        static Handle proxy ( ::HANDLE object );

        static void install (
            const string& name, const string& path,
            const string& categories, dword count );

        static void remove ( const string& name );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    protected:
        explicit Log ( const Handle& handle );

    public:
        Log ( const string& name );

        /* methods. */
    public:
        const Handle& handle () const;
        void report ( const Event& event );
    };

} }

#endif /* _w32_dbg_Log_hpp__ */
