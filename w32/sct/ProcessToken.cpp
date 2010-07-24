/*!
 * @file ProcessToken.cpp
 * @author Andre Caron
 */

#include "ProcessToken.hpp"
#include <win32c/diagnostics/UncheckedError.hpp>

namespace {

    ::HANDLE open ( ::HANDLE process, ::DWORD access )
    {
        ::HANDLE handle = 0;
        if ( ::OpenProcessToken(process,access,&handle) == 0 ) {
            UNCHECKED_WIN32C_ERROR(OpenProcessToken,::GetLastError());
        }
        return (handle);
    }

}

namespace win32c {
    namespace security {

        ProcessToken::Handle::Handle ( ::HANDLE value )
            : myValue(value)
        {
        }

        ProcessToken::Handle::~Handle ()
        {
            if ( ::CloseHandle(myValue) == 0 ) {
                UNCHECKED_WIN32C_ERROR(CloseHandle,::GetLastError());
            }
        }

        ::HANDLE ProcessToken::Handle::value () const
        {
            return (myValue);
        }

        ProcessToken::ProcessToken ( const pmgt::Process& process )
            : myHandle(open(process.handle().value(),TOKEN_ALL_ACCESS))
        {
        }

        const ProcessToken::Handle& ProcessToken::handle () const
        {
            return (myHandle);
        }

    }
}
