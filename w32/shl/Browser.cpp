// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Browser.hpp>

namespace w32 { namespace shl {

    Browser::Browser ()
    {
        ::ZeroMemory(&myData, sizeof(myData));
    }

    Browser::Browser ( const Hints& hints )
    {
        ::ZeroMemory(&myData, sizeof(myData));
        myData.ulFlags = hints;
    }

    void Browser::title ( const w32::string& text )
    {
        myData.lpszTitle = text.data();
    }

    Path Browser::prompt ()
    {
        const ::PIDLIST_ABSOLUTE result = ::SHBrowseForFolderW(&myData);
        if ( result == 0 ) {
            return (L"");
        }
        return (Path(result));
    }

    const Browser::Hints Browser::Hints::folders ()
    {
        return (BIF_RETURNONLYFSDIRS);
    }

    Browser::Hints::Hints ( Value value )
        : myValue(value)
    {
    }

    Browser::Hints::Value Browser::Hints::value () const
    {
        return (myValue);
    }

    Browser::Hints::operator Browser::Hints::Value () const
    {
        return (myValue);
    }

    Browser::Hints& Browser::Hints::operator|= ( const Hints& rhs )
    {
        myValue |= rhs.myValue; return (*this);
    }

    Browser::Hints Browser::Hints::operator| ( const Hints& rhs )
    {
        Hints result(*this); result |= rhs; return (result);
    }

} }
