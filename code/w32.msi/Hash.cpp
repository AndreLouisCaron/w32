// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.msi/Hash.hpp>
#include <w32/Error.hpp>
#include <iomanip>
#include <iostream>

namespace {

    ::MSIFILEHASHINFO compute ( const char * path )
    {
        ::MSIFILEHASHINFO hash = { sizeof(::MSIFILEHASHINFO), { 0, 0, 0, 0 } };
        const ::UINT result = ::MsiGetFileHashA(path,0,&hash);
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_WIN32C_ERROR(MsiGetFileHash,result);
        }
        return (hash);
    }

    std::ostream& u32 ( std::ostream& out ) {
        return (out << std::hex << std::setfill('0') << std::setw(8));
    }

}

namespace w32 { namespace msi {

    Hash::Hash ( const char * path )
        : myValue(compute(path))
    {
    }

    Hash::Value& Hash::value ()
    {
        return (myValue);
    }

    const Hash::Value& Hash::value () const
    {
        return (myValue);
    }

    std::ostream& operator<< ( std::ostream& out, const Hash& hash )
    {
        out << u32 << hash.value().dwData[0]
            << u32 << hash.value().dwData[1]
            << u32 << hash.value().dwData[2]
            << u32 << hash.value().dwData[3];
        return (out);
    }

} }
