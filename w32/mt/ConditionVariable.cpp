// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/mt/ConditionVariable.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace mt {

    ConditionVariable::ConditionVariable ()
    {
        ::InitializeConditionVariable(&myData);
    }

    ConditionVariable::~ConditionVariable ()
    {
    }

    ConditionVariable::Data& ConditionVariable::data ()
    {
        return (myData);
    }

    const ConditionVariable::Data& ConditionVariable::data () const
    {
        return (myData);
    }

    void ConditionVariable::signal ()
    {
        ::WakeConditionVariable(&myData);
    }

    void ConditionVariable::broadcast ()
    {
        ::WakeAllConditionVariable(&myData);
    }

    void ConditionVariable::sleep ( CriticalSection& lock )
    {
        const ::BOOL result = ::SleepConditionVariableCS(
            &myData, &lock.data(), INFINITE
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SleepConditionVariableCS, error);
        }
    }

    void ConditionVariable::sleep ( ReadWriteLock& lock, bool shared )
    {
        const ::ULONG flags = ((shared)? CONDITION_VARIABLE_LOCKMODE_SHARED:0);
        const ::BOOL result = ::SleepConditionVariableSRW(
            &myData, &lock.data(), INFINITE, flags
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SleepConditionVariableCS, error);
        }
    }

} }
