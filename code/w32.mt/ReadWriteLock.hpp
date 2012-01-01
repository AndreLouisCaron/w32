#ifndef _w32_mt_ReadWriteLock_hpp__
#define _w32_mt_ReadWriteLock_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"

    // Sanity check.
#if (_WIN32_WINNT < 0x600)
#   error "Requires Windows Vista or later versions."
#endif

#include <w32/NotCopyable.hpp>

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Mutual exclusion lock with exclusive or shared access.
     *
     * For some problems, pure mutual exclusion locks are too restrictive.  When
     * read-only access to a resource is already thread-safe, it makes no sense
     * for reader threads to deny each other concurrent access.  Reader-writer
     * locks grant exclusive write-safe access for write operations (this blocks
     * any other reader or writer) or shared read-safe access for read
     * operations (this blocks out all writers but allows other readers).
     *
     * @see CriticalSection
     * @see Mutex
     */
    class ReadWriteLock :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SRWLOCK Data;

        class ReadGuard :
            private w32::NotCopyable
        {
            /* data. */
        private:
            Data& myLock;

            /* construction. */
        public:
            ReadGuard ( ReadWriteLock& lock );
            ~ReadGuard ();
        };

        class WriteGuard :
            private w32::NotCopyable
        {
            /* data. */
        private:
            Data& myLock;

            /* construction. */
        public:
            WriteGuard ( ReadWriteLock& lock );
            ~WriteGuard ();
        };

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        ReadWriteLock ();
        ~ReadWriteLock ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
    };

} }

#endif /* _w32_mt_ReadWriteLock_hpp__ */
