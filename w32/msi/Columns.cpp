// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/Columns.hpp>
#include <w32/msi/Error.hpp>

namespace {

    ::MSIHANDLE columns ( ::MSIHANDLE view, ::MSICOLINFO information )
    {
        ::MSIHANDLE record = 0;
        const ::UINT result = ::MsiViewGetColumnInfo(view,information,&record);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_FUNCTION_FAILED ) {
                throw (w32::msi::View::FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (w32::msi::View::InvalidHandle());
            }
            else if ( result == ERROR_INVALID_HANDLE_STATE ) {
                throw (w32::msi::View::InvalidState());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (w32::msi::View::InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiViewGetColumnInfo,result);
        }
        return (record);
    }
}

namespace w32 { namespace msi {

    Columns::Columns ( const View& view, const View::Column& information )
        : Record( ::columns(view.handle(), information.value() ))
    {
    }

} }
