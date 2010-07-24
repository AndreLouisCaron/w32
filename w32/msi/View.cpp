// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/View.hpp>
#include <w32/msi/Record.hpp>
#include <w32/msi/Error.hpp>

namespace {

    ::MSIHANDLE open ( ::MSIHANDLE database, const wchar_t * query )
    {
        ::MSIHANDLE handle = 0;
        const ::UINT result = ::MsiDatabaseOpenViewW(database,query,&handle);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_BAD_QUERY_SYNTAX ) {
                throw (w32::msi::View::BadSqlSyntax());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (w32::msi::View::InvalidHandle());
            }
            UNCHECKED_INSTALLER_ERROR(MsiDatabaseOpenView,result);
        }
        return (handle);
    }

}

namespace w32 { namespace msi {

    View::Column::Column ( Value value )
        : myValue(value)
    {
    }

    View::Column::Value View::Column::value () const
    {
        return (myValue);
    }

    View::View ( const Handle& handle )
        : Object(handle)
    {
    }

    View::View ( const Database& database, const string& query )
        : Object(claim(::open(database.handle(), query.c_str())))
    {
    }

    void View::execute ()
    {
        const ::UINT result = ::MsiViewExecute(handle(),0);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_FUNCTION_FAILED ) {
                throw (FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            UNCHECKED_INSTALLER_ERROR(MsiViewExecute,result);
        }
    }

    void View::close ()
    {
        const ::UINT result = ::MsiViewClose(handle());
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_FUNCTION_FAILED ) {
                throw (FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_HANDLE_STATE ) {
                throw (InvalidState());
            }
            UNCHECKED_INSTALLER_ERROR(MsiViewClose,result);
        }
    }

} }
