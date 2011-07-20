// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/ipc/Modules.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE snapshot ( ::DWORD process )
    {
        const ::HANDLE result =
            ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process);
        if ( result == INVALID_HANDLE_VALUE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(CreateToolhelp32Snapshot, error);
        }
        return (result);
    }

}

namespace w32 { namespace ipc {

    Modules::Modules ( Process::Identifier process )
        : Object(claim( ::snapshot(process) ))
    {
    }

    Modules::Modules ( const Process& process )
        : Object(claim( ::snapshot(process.identifier()) ))
    {
    }

    bool Modules::find ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Module32FirstW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(Module32FirstW, error);
        }
        return (true);
    }

    bool Modules::next ( Entry& entry )
    {
        entry.clear();
        const ::BOOL result = ::Module32NextW(handle(), &entry.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(Module32FirstW, error);
        }
        return (true);
    }

    Modules::Entry::Entry ()
    {
        clear();
    }

    Modules::Entry::Data& Modules::Entry::data ()
    {
        return (myData);
    }

    const Modules::Entry::Data& Modules::Entry::data () const
    {
        return (myData);
    }

    void Modules::Entry::clear ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.dwSize = sizeof(myData);
    }

    const pointer Modules::Entry::base () const
    {
        return (myData.modBaseAddr);
    }

    const string Modules::Entry::name () const
    {
        return (myData.szModule);
    }

    const string Modules::Entry::path () const
    {
        return (myData.szExePath);
    }

} }
