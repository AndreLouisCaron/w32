// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ipc/Processes.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ()
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Processes::Processes ()
        : Object(claim( ::snapshot() ))
    {
    }

    bool Processes::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Process32FirstW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Process32FirstW, error);
        }
        return (true);
    }

    bool Processes::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Process32NextW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Process32FirstW, error);
        }
        return (true);
    }

    Processes::Entry::Entry ()
    {
        clear();
    }

    Processes::Entry::Data& Processes::Entry::data ()
    {
        return (myData);
    }

    const Processes::Entry::Data& Processes::Entry::data () const
    {
        return (myData);
    }

    void Processes::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const Process Processes::Entry::self () const
    {
        return (Process(myData.th32ProcessID));
    }

    const Process Processes::Entry::parent () const
    {
        return (Process(myData.th32ParentProcessID));
    }

    const dword Processes::Entry::threads () const
    {
        return (myData.cntThreads);
    }

    const string Processes::Entry::executable () const
    {
        return (myData.szExeFile);
    }

} }
