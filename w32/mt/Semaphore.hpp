#ifndef _w32_mt_Semaphore_hpp__
#define _w32_mt_Semaphore_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

    class W32_MT_EXPORT Semaphore :
        public Waitable
    {
        /* nested types. */
    public:
            /*!
             * @brief Scoped ownership.
             */
        class Lock :
            private NotCopyable
        {
            /* data. */
        private:
            Semaphore& mySemaphore;

            /* construction. */
        public:
            explicit Lock ( Semaphore& mutex );
            Lock ( Semaphore& mutex, const Timespan& timeout );
            ~Lock ();
        };

        /* construction. */
    public:
        Semaphore ( long initial, long maximum );

        /* methods. */
    public:
            /*!
             * @brief Waits until a share of the semaphore lock is available.
             */
        void acquire ();

            /*!
             * @brief Waits until a share of the semaphore lock is available, or
             *    until the timeout expires.
             *
             * @return False if the timeout expired.
             */
        bool acquire ( const Timespan& timeout );

            /*!
             * @brief Makes the lock available for another thread.
             * @param Number of shares to release.
             * @param Number of available shares, after the release operation.
             */
        long release ( long count = 1 );
    };

} }

#endif /* _w32_mt_Semaphore_hpp__ */
