// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/ErrorRecord.hpp>
#include <w32/msi/Error.hpp>

namespace {

    ::MSIHANDLE get ()
    {
        return (::MsiGetLastErrorRecord());
    }

}

namespace w32 { namespace msi {

    ErrorRecord::ErrorRecord ()
        : Object(claim(::get()))
    {
    }

    uint ErrorRecord::fields () const
    {
        const ::UINT result = ::MsiRecordGetFieldCount(handle());
        if ( result == static_cast<::UINT>(-1) ) {
            UNCHECKED_INSTALLER_ERROR(MsiRecordGetFieldCount,result);
        }
        return (result);
    }

    int ErrorRecord::field ( uint index ) const
    {
        return (::MsiRecordGetInteger(handle(),index));
    }

} }
