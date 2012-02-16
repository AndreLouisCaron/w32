#ifndef _w32_mt_atomic_hpp__
#define _w32_mt_atomic_hpp__

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
#include <w32.mt/and.hpp>
#include <w32.mt/compare-exchange.hpp>
#include <w32.mt/decrement.hpp>
#include <w32.mt/exchange.hpp>
#include <w32.mt/increment.hpp>
#include <w32.mt/or.hpp>
#include <w32.mt/xor.hpp>

namespace w32 { namespace mt {

    template<typename T> class atomic;

    /*!
     * @brief Thread-safe 32-bit signed integer.
     */
    template<> class atomic<int32>
    {
        /* nested types. */
    private:
        typedef atomic<int32> self;

    public:
        /*!
         * @brief Native representation.
         */
        typedef volatile __declspec(align(32)) ::LONG Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        atomic ( int32 value=0 )
            : myValue(value)
        {}

        /* methods. */
    public:
        self& exchange ( int32 replacement )
        {
            mt::exchange
                (myValue, replacement);
            return (*this);
        }

        self& exchange_acquire ( int32 replacement )
        {
            mt::exchange_acquire
                (myValue, replacement);
            return (*this);
        }

        self& compare_exchange ( int32 test, int32 replacement )
        {
            mt::compare_exchange
                (test, myValue, replacement);
            return (*this);
        }

        self& compare_exchange_acquire ( int32 test, int32 replacement )
        {
            mt::compare_exchange_acquire
                (test, myValue, replacement);
            return (*this);
        }

        /* operators. */
    public:
        // compiler-generated version is not atomic.
        self& operator= ( const self& rhs )
        {
            return (exchange(rhs));
        }

        self& operator= ( int32 rhs )
        {
            return (exchange(rhs));
        }

        operator int32 () const
        {
            return (myValue);
        }

        self& operator++ ()
        {
            increment(myValue); return (*this);
        }

        self& operator-- ()
        {
            decrement(myValue); return (*this);
        }

        self& operator&= ( int32 rhs )
        {
            and(myValue, rhs); return (*this);
        }

        self& operator|= ( int32 rhs )
        {
            or(myValue, rhs); return (*this);
        }

        self& operator^= ( int32 rhs )
        {
            xor(myValue, rhs); return (*this);
        }
    };

    /*!
     * @brief Thread-safe 64-bit signed integer.
     */
    template<> class atomic<int64>
    {
        /* nested types. */
    private:
        typedef atomic<int64> self;

    public:
        /*!
         * @brief Native representation.
         */
        typedef volatile __declspec(align(64)) ::LONG Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        atomic ( int64 value=0 )
            : myValue(value)
        {}

        /* methods. */
    public:
        self& exchange ( int64 replacement )
        {
            mt::exchange
                (myValue, replacement);
            return (*this);
        }

        self& exchange_acquire ( int64 replacement )
        {
            mt::exchange_acquire
                (myValue, replacement);
            return (*this);
        }

        self& compare_exchange ( int64 test, int64 replacement )
        {
            mt::compare_exchange
                (test, myValue, replacement);
            return (*this);
        }

        self& compare_exchange_acquire ( int64 test, int64 replacement )
        {
            mt::compare_exchange_acquire
                (test, myValue, replacement);
            return (*this);
        }

        /* operators. */
    public:
        // compiler-generated version is not atomic.
        self& operator= ( const self& rhs )
        {
            return (exchange(rhs));
        }

        self& operator= ( int64 rhs )
        {
            return (exchange(rhs));
        }

        operator int64 () const
        {
            return (myValue);
        }

        self& operator++ ()
        {
            increment(myValue); return (*this);
        }

        self& operator-- ()
        {
            decrement(myValue); return (*this);
        }

        self& operator&= ( int64 rhs )
        {
            and(myValue, rhs); return (*this);
        }

        self& operator|= ( int64 rhs )
        {
            or(myValue, rhs); return (*this);
        }

        self& operator^= ( int64 rhs )
        {
            xor(myValue, rhs); return (*this);
        }
    };

    /*!
     * @brief Thread-safe pointer variable.
     */
    template<> class atomic<void*>
    {
        /* nested types. */
    private:
        typedef atomic<void*> self;

    public:
        /*!
         * @brief Native representation.
         */
#if defined(_M_IX86)
        typedef volatile __declspec(align(32)) ::PVOID Value;
#else
        typedef volatile __declspec(align(64)) ::PVOID Value;
#endif

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        atomic ( void * value=0 )
            : myValue(value)
        {}

        /* methods. */
    public:
        self& exchange ( void * replacement )
        {
            mt::exchange
                (myValue, replacement);
            return (*this);
        }

        self& exchange_acquire ( void * replacement )
        {
            mt::exchange_acquire
                (myValue, replacement);
            return (*this);
        }

        self& compare_exchange ( void * test, void * replacement )
        {
            mt::compare_exchange
                (test, myValue, replacement);
            return (*this);
        }

        self& compare_exchange_acquire ( void * test, void * replacement )
        {
            mt::compare_exchange_acquire
                (test, myValue, replacement);
            return (*this);
        }

        /* operators. */
    public:
        // compiler-generated version is not atomic.
        self& operator= ( const self& rhs )
        {
            return (exchange(rhs));
        }

        self& operator= ( void * rhs )
        {
            return (exchange(rhs));
        }

        operator void* () const
        {
            return (myValue);
        }
    };

} }

#endif /* _w32_mt_atomic_hpp__ */
