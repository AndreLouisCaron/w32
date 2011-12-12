// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.ipc/Threads.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ()
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Threads::Threads ()
        : Object(claim( ::snapshot() ))
    {
    }

    bool Threads::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Thread32First(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Thread32First, error);
        }
        return (true);
    }

    bool Threads::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Thread32Next(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Thread32First, error);
        }
        return (true);
    }

    Threads::Entry::Entry ()
    {
        clear();
    }

    Threads::Entry::Data& Threads::Entry::data ()
    {
        return (myData);
    }

    const Threads::Entry::Data& Threads::Entry::data () const
    {
        return (myData);
    }

    void Threads::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const mt::Thread Threads::Entry::self () const
    {
        return (mt::Thread::open(myData.th32ThreadID));
    }

    const Process Threads::Entry::process () const
    {
        return (Process(myData.th32OwnerProcessID));
    }

} }
