#ifndef _w32_mt_Fiber_hpp__
#define _w32_mt_Fiber_hpp__

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
#include <w32/Reference.hpp>

namespace w32 { namespace mt {

    /*!
     * @brief Userspace thread with cooperative scheduling.
     *
     * @see start_fiber()
     * @see yield_to()
     */
    class Fiber
    {
        /* nested types. */
    public:
        typedef Reference<void*> Handle;
        typedef void * Context;

        typedef void(__stdcall*Entry)(Context);

        template<void(*)(void*)> struct function;
        template<typename T, void(T::*)()> struct method;

        /* class methods. */
    public:
        static Handle claim (void * object);
        static Handle proxy (void * object);

        static Fiber current ();

        static Context context ();

        template<typename T>
        static T context () {
            return (static_cast<T>(context()));
        }

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Fiber ();
        explicit Fiber (const Handle& handle);
        Fiber (Entry entry, Context context=0, size_t stack_size=0);

        /* methods. */
    public:
        const Handle& handle () const;

        /*!
         * @brief Pass control to this fiber.
         *
         * @note Control will return to this fiber when another fiber
         *  explicitly yields control back to this fiber.
         */
        void yield_to ();
    };

    bool operator== (const Fiber& lhs, const Fiber& rhs);
    bool operator!= (const Fiber& lhs, const Fiber& rhs);

    // compile-time binding of free function to callback function.
    template<void(*F)(void*)>
    struct Fiber::function
    {
        operator ::LPFIBER_START_ROUTINE () const
        {
            return (&entry_point);
        }

    private:
        static void __stdcall entry_point (::LPVOID context)
        {
            return (F(context));
        }
    };

    template<typename T, void(T::*M)()>
    struct Fiber::method
    {
        operator ::LPFIBER_START_ROUTINE () const
        {
            return (&entry_point);
        }

    private:
        static void __stdcall entry_point (::LPVOID context)
        {
            return ((static_cast<T*>(context)->*M)());
        }
    };

    /*!
     * @brief Enable support for fibers in the current thread.
     * @return The fiber handle for the current thread.
     */
    Fiber start_fiber (Fiber::Context context=0);

} }

#endif /* _w32_mt_Fiber_hpp__ */
