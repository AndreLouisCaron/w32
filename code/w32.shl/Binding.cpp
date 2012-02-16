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

#include <w32.shl/Binding.hpp>
#include <w32.com/Error.hpp>

namespace {

    ::IBindCtx * allocate ()
    {
        ::IBindCtx * binding = 0;
        const w32::com::Result result = ::CreateBindCtx(0, &binding);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, CreateBindCtx, result);
        }
        return (binding);
    }

}

namespace w32 { namespace shl {

    Binding::Binding ()
        : com::Wrapper< ::IBindCtx >( ::allocate() )
    {
    }

    Binding::Options Binding::options () const
    {
        Options options;
        const com::Result result = ptr()->GetBindOptions(&options.data());
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IBindCtx, GetBindOptions, result);
        }
        return (options);
    }

    void Binding::options ( const Options& options )
    {
        const com::Result result =
            ptr()->SetBindOptions(const_cast< ::BIND_OPTS* >(&options.data()));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IBindCtx, SetBindOptions, result);
        }
    }

    Binding::Options::Options ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.cbStruct = sizeof(myData);
    }

    Binding::Options::Data& Binding::Options::data ()
    {
        return (myData);
    }

    const Binding::Options::Data& Binding::Options::data () const
    {
        return (myData);
    }

    void Binding::Options::access ( dword access )
    {
        myData.grfMode = access;
    }

} }
