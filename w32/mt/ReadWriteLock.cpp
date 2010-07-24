// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/ReadWriteLock.hpp>

namespace w32 { namespace mt {

    ReadWriteLock::ReadGuard::ReadGuard ( ReadWriteLock& lock )
        : myLock(lock.data())
    {
        ::AcquireSRWLockShared(&myLock);
    }

    ReadWriteLock::ReadGuard::~ReadGuard ()
    {
        ::ReleaseSRWLockShared(&myLock);
    }

    ReadWriteLock::WriteGuard::WriteGuard ( ReadWriteLock& lock )
        : myLock(lock.data())
    {
        ::AcquireSRWLockExclusive(&myLock);
    }

    ReadWriteLock::WriteGuard::~WriteGuard ()
    {
        ::ReleaseSRWLockExclusive(&myLock);
    }

    ReadWriteLock::ReadWriteLock ()
    {
        ::InitializeSRWLock(&myData);
    }

    ReadWriteLock::~ReadWriteLock ()
    {
    }

    ReadWriteLock::Data& ReadWriteLock::data ()
    {
        return (myData);
    }

    const ReadWriteLock::Data& ReadWriteLock::data () const
    {
        return (myData);
    }

} }
