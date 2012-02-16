#ifndef _w32_com_Factory_hpp__
#define _w32_com_Factory_hpp__

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
#include <w32.com/Model.hpp>
#include <memory>

namespace w32{ namespace com {

        /*!
         * @brief Implements boiler-plate code for a simple factory.
         */
    template<typename Class>
    class Factory :
        public Model< ::IClassFactory >
    {
        /* methods. */
    public:
        ::HRESULT __stdcall LockServer ( ::BOOL lock ) {
            return (E_NOTIMPL);
        }

        ::HRESULT __stdcall CreateInstance (
            ::IUnknown * object, const ::GUID& guid, void ** output
            );
    };

    template<typename Class>
    ::HRESULT __stdcall Factory<Class>::CreateInstance (
        ::IUnknown * object, const ::GUID& guid, void ** output
        )
    try
    {
        if ( object != 0 ) {
            return (CLASS_E_NOAGGREGATION);
        }
        const Ptr<Class> instance(new Class());
        return (instance->QueryInterface(guid,output));
    }
    catch ( const std::bad_alloc& ) {
        return (E_OUTOFMEMORY);
    }
    catch ( ... ) {
        return (E_FAIL);
    }

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IClassFactory > ()
{
    return (IID_IClassFactory);
}

#endif /* _w32_com_Factory_hpp__ */
