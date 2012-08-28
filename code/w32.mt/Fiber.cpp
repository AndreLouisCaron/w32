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

#include <w32.mt/Fiber.hpp>
#include <w32/Error.hpp>

namespace {

    void * allocate (LPFIBER_START_ROUTINE entry,
                     void * context, ::SIZE_T stack_size)
    {
        void *const handle = ::CreateFiber(stack_size, entry, context);
        if (handle == 0)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConvertThreadToFiberEx, error);
        }
        return (handle);
    }

    void abandon (void * object) {}
    void release (void * object)
    {
        ::DeleteFiber(object);
    }

}

namespace w32 { namespace mt {

    Fiber::Handle Fiber::claim (void * object)
    {
        return (Handle(object, &::release));
    }

    Fiber::Handle Fiber::proxy (void * object)
    {
        return (Handle(object, &::abandon));
    }

    Fiber Fiber::current ()
    {
        void *const handle = GetCurrentFiber();
        // TODO: check for null fiber?
        return (Fiber(proxy(handle)));
    }

    Fiber::Context Fiber::context ()
    {
        return (GetFiberData());
    }

    Fiber::Fiber ()
        : myHandle(proxy(0))
    {
    }

    Fiber::Fiber (const Handle& handle)
        : myHandle(handle)
    {
    }

    Fiber::Fiber (Entry entry, Context context, size_t stack_size)
        : myHandle(claim(::allocate(entry, context, stack_size)))
    {
    }

    const Fiber::Handle& Fiber::handle () const
    {
        return (myHandle);
    }

    void Fiber::yield_to ()
    {
        // The documentation specifically warns against trying to switch to the
        // current fiber, saying that it could cause "unpredictable problems"!
        if (myHandle == GetCurrentFiber()) {
            return;
        }
        ::SwitchToFiber(myHandle);
    }

    Fiber start_fiber (Fiber::Context context)
    {
        // Prevent double "conversion".
#if _WIN32_WINNT >= _WIN32_WINNT_VISTA
        if (::IsThreadAFiber()) {
            return (Fiber::current());
        }
#endif

        void *const handle = ::ConvertThreadToFiberEx
            (context, FIBER_FLAG_FLOAT_SWITCH);
        if (handle == 0)
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ConvertThreadToFiberEx, error);
        }
        return (Fiber(Fiber::proxy(handle)));
    }

    bool operator== (const Fiber& lhs, const Fiber& rhs)
    {
        return (lhs.handle() == rhs.handle());
    }

    bool operator!= (const Fiber& lhs, const Fiber& rhs)
    {
        return (lhs.handle() != rhs.handle());
    }

} }
