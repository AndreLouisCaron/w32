// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/rgs/Keys.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace rgs {

    Keys::Keys ( const Key& key )
        : myKey(key), myIndex(0), myResult(ERROR_SUCCESS)
    {
        myName[0] = L'\0';
    }

    const wchar_t * Keys::result () const
    {
        return (myName);
    }

    bool Keys::next ()
    {
        myName[0] = L'\0';
        dword length = 255;
        myResult = ::RegEnumKeyExW(
            myKey.handle(), myIndex, myName, &length, 0, 0, 0, 0
            );
        if ( myResult == ERROR_NO_MORE_ITEMS ) {
            return (false);
        }
        ++myIndex;
        if ( myResult != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegEnumKeyEx,myResult);
        }
        myName[length] = L'\0';
        return (true);
    }

} }
