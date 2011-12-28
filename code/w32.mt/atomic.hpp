#ifndef _w32_mt_atomic_hpp__
#define _w32_mt_atomic_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
