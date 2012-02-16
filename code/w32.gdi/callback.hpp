#ifndef _w32_gdi_callback_hpp__
#define _w32_gdi_callback_hpp__

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

namespace w32 { namespace gdi {

        // Placeholder for conversion to universal event handler.
        // Tries to preserve the argument type for compile-time
        // validation against the Notification<> argument type.
    template<class M, class A>
    class delegate
    {
    protected:
            // Universal function prototype.
        typedef void(*backend)(M&,const ::NMHDR*);
    private:
        backend myBackend;
    protected:
            // Base classes provide callback function.
        delegate ( backend function ) : myBackend(function) {}
    public:
        operator backend () const { return (myBackend); }
    };

        // Generic case for a real callback.
    template<class M, class A, void(M::*F)(A)>
    struct callback;

        // Specific case for a WM_NOTIFY handler.
    template<class M, class A, void(M::*F)(A)>
    class callback<M, A, F> : public delegate< M, A >
    {
        static void function ( M& m, const ::NMHDR * h )
        {
            (m.*F)(*reinterpret_cast<const A*>(h));
        }
    public:
        callback () : delegate<M,A>(&function) {}
    };

        // Specific case for a WM_COMMAND handler.
    template<class M, void(M::*F)()>
    class callback<M, void, F> : public delegate< M, void >
    {
        static void function ( M& m, const ::NMHDR * h )
        {
            (m.*F)();
        }
    public:
        callback () : delegate<M,void>(&function) {}
    };

} }

#endif /* _w32_gdi_callback_hpp__ */
