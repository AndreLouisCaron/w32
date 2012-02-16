// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.msi/View.hpp>
#include <w32.msi/Record.hpp>
#include <w32.msi/Error.hpp>

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

    const View::Column View::Column::names ()
    {
        return (MSICOLINFO_NAMES);
    }

    const View::Column View::Column::types ()
    {
        return (MSICOLINFO_TYPES);
    }

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
