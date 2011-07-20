// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/gdi/Atom.hpp>
#include <w32/Error.hpp>

namespace {

        // Search in the global atom table as a last resort.
    ::ATOM gfind ( ::LPCWSTR name )
    {
        const ::ATOM atom = ::GlobalFindAtomW(name);
        if ( atom == 0 ) {
            UNCHECKED_WIN32C_ERROR(FindAtom, ::GetLastError());
        }
        return (atom);
    }

        // Search in the local table first, then in the global table if missing.
    ::ATOM find ( ::LPCWSTR name )
    {
        const ::ATOM atom = ::FindAtomW(name);
        if ( atom == 0 )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_FILE_NOT_FOUND ) {
                return (gfind(name));
            }
            UNCHECKED_WIN32C_ERROR(FindAtom, ::GetLastError());
        }
        return (atom);
    }

}

namespace w32 { namespace gdi {

    Atom::Atom ( Id id )
        : myId(id)
    {
    }

    Atom::Atom ( const string& name )
        : myId(::find(name.c_str()))
    {
    }

    Atom::Id Atom::id () const
    {
        return (myId);
    }

    bool Atom::bad () const
    {
        return (id() == 0);
    }

    bool Atom::ok () const
    {
        return (id() != 0);
    }

    const wchar_t * Atom::raw () const
    {
        return ((::LPCWSTR)(ulongptr(word(id()))));
    }

} }
