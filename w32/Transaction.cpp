
#include <w32/Transaction.hpp>
#include <w32/Error.hpp>
#include <KtmW32.h>
#pragma comment ( lib, "KtmW32.lib" )

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
