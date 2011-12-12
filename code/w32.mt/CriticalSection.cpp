// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.mt/CriticalSection.hpp>

namespace w32 { namespace mt {

    CriticalSection::CriticalSection ()
    {
        ::InitializeCriticalSection(&myData);
    }

    CriticalSection::~CriticalSection ()
    {
        ::DeleteCriticalSection(&myData);
    }

    CriticalSection::Data& CriticalSection::data ()
    {
        return (myData);
    }

    const CriticalSection::Data& CriticalSection::data () const
    {
        return (myData);
    }

    void CriticalSection::enter ()
    {
        ::EnterCriticalSection(&myData);
    }

    bool CriticalSection::tryenter ()
    {
        return (::TryEnterCriticalSection(&myData) != FALSE);
    }

    void CriticalSection::leave ()
    {
        ::LeaveCriticalSection(&myData);
    }

    CriticalSection::Lock::Lock ( CriticalSection& mutex )
        : mySection(mutex)
    {
        mySection.enter();
    }

    CriticalSection::Lock::~Lock ()
    {
        mySection.leave();
    }


} }
