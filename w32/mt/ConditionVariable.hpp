#ifndef _w32_mt_ConditionVariable_hpp__
#define _w32_mt_ConditionVariable_hpp__

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
#include <w32/mt/CriticalSection.hpp>
#include <w32/mt/ReadWriteLock.hpp>

namespace w32 { namespace mt {

    class W32_MT_EXPORT ConditionVariable :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::CONDITION_VARIABLE Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        ConditionVariable ();
        ~ConditionVariable ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void signal ();
        void broadcast ();
        void sleep ( CriticalSection& lock );
        void sleep ( ReadWriteLock& lock, bool shared=false );
    };

} }

#endif /* _w32_mt_ConditionVariable_hpp__ */
