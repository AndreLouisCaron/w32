// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.rgs/Values.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace rgs {

    Values::Values ( const Key& key )
        : myKey(key), myIndex(0), myType(0), myResult(ERROR_SUCCESS)
    {
        ::ZeroMemory(myName, sizeof(myName));
    }

    const wchar_t * Values::result () const
    {
        return (myName);
    }

    bool Values::next ()
    {
        myName[0] = L'\0';
        ::DWORD length = 255;
        myResult = ::RegEnumValueW(
            myKey.handle(), myIndex, myName, &length, 0, &myType, 0, 0
            );
        if ( myResult == ERROR_NO_MORE_ITEMS ) {
            return (false);
        }
        ++myIndex;
        if ( myResult != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(RegEnumValue,myResult);
        }
        myName[length] = L'\0';
        return (true);
    }

} }
