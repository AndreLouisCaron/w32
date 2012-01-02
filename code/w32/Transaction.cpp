// Copyright(c) Andre Caron, 2009-2012
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

/*!
 * @file w32/Transaction.cpp
 * @author Andre Caron
 */

#include <w32/Transaction.hpp>
#include <w32/Error.hpp>
#include <KtmW32.h>

namespace {

    ::HANDLE create ( ::LPCWSTR description )
    {
        const ::DWORD options = 0;
        const ::DWORD timeout = 0;
        const ::HANDLE handle = ::CreateTransaction(
            0, 0, options, 0, 0, timeout, const_cast< ::LPWSTR >(description)
            );
        if ( handle == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateTransaction, error);
        }
        return (handle);
    }

}

namespace w32 {

    Transaction::Transaction ()
        : Object(claim(::create(0)))
    {
    }

    Transaction::Transaction ( const string& description )
        : Object(claim(::create(description.data())))
    {
    }

    void Transaction::commit ()
    {
        const ::BOOL result = ::CommitTransaction(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CommitTransaction, error);
        }
    }

    void Transaction::rollback ()
    {
        const ::BOOL result = ::RollbackTransaction(handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RollbackTransaction, error);
        }
    }

}
