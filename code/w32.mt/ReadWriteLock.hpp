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
