#ifndef _w32_mt_Mutex_hpp__
#define _w32_mt_Mutex_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/string.hpp>
#include <w32/Waitable.hpp>

namespace w32 { namespace mt {

        /*!
         * @brief Mutual-exclusion lock.
         */
    class Mutex :
        public Object
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
            Mutex& myMutex;

            /* construction. */
        public:
            explicit Lock ( Mutex& mutex );
            Lock ( Mutex& mutex, const Timespan& timeout );
            ~Lock ();
        };

        /* class methods. */
    public:
        static Mutex open ( const string& name );

        /* construction. */
    protected:
        explicit Mutex ( const Handle& handle );

    public:
        Mutex ();
        explicit Mutex ( const string& name );

        /* methods. */
    public:
            /*!
             * @brief Waits until the mutex lock is available.
             */
        void acquire ();

            /*!
             * @brief Waits until the mutex lock is available, or until the
             *    timeout expires.
             *
             * @return False if the timeout expired.
             */
        bool acquire ( const Timespan& timeout );

            /*!
             * @brief Makes the lock available for another thread.
             */
        void release ();

        /* operators. */
    public:
        operator Waitable () const;
    };

} }

#endif /* _w32_mt_Mutex_hpp__ */
