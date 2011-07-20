// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Location.hpp>

namespace w32 { namespace shl {

    const Location Location::computer ()
    {
        return (CSIDL_DRIVES);
    }

    const Location Location::desktop ()
    {
        return (CSIDL_DESKTOPDIRECTORY);
    }

    const Location Location::fonts ()
    {
        return (CSIDL_FONTS);
    }

    const Location Location::programs ()
    {
        return (CSIDL_PROGRAMS);
    }

    const Location Location::start ()
    {
        return (CSIDL_STARTMENU);
    }

    const Location Location::startup ()
    {
        return (CSIDL_STARTUP);
    }

    const Location Location::system ()
    {
        return (CSIDL_SYSTEM);
    }

    const Location Location::windows ()
    {
        return (CSIDL_WINDOWS);
    }

    Location::Location ( Value value )
        : myValue(value)
    {
    }

    Location::Value Location::value () const
    {
        return (myValue);
    }

    Location::operator Location::Value () const
    {
        return (myValue);
    }

    Location::operator Path () const
    {
        ::LPITEMIDLIST path = 0;
        const com::Result result = ::SHGetFolderLocation(
            0, myValue, 0, 0, &path
            );
        if ( result.bad() ) {
            throw std::exception("SHGetFolderLocation");
        }
        return (Path::box(path));
    }

} }
