#ifndef _w32_mt_decrement_hpp__
#define _w32_mt_decrement_hpp__

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
#include <w32/types.hpp>

namespace w32 { namespace mt {

    inline ::LONG decrement ( volatile ::LONG& x )
    {
        return InterlockedDecrement(&x);
    }

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
    inline ::LONGLONG decrement ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrement64(&x);
    }
#endif

    inline ::LONG decrement_acquire ( volatile ::LONG& x )
    {
        return InterlockedDecrementAcquire(&x);
    }

#ifdef _M_IA64
    inline ::LONGLONG decrement_acquire ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrementAcquire64(&x);
    }
#endif

    inline ::LONG decrement_release ( volatile ::LONG& x )
    {
        return InterlockedDecrementRelease(&x);
    }

#ifdef _M_IA64
    inline ::LONGLONG decrement_release ( volatile ::LONGLONG& x )
    {
        return InterlockedDecrementRelease64(&x);
    }
#endif

} }

#endif /* _w32_mt_decrement_hpp__ */
