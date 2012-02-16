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

#include <w32.msi/Database.hpp>
#include <w32.msi/Error.hpp>
#include <w32.msi/ErrorRecord.hpp>

namespace {

    ::MSIHANDLE open ( const wchar_t * path, ::LPCWSTR mode )
    {
        ::MSIHANDLE value = 0;
        const ::UINT result = ::MsiOpenDatabaseW(path,mode,&value);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_CREATE_FAILED ) {
                throw (w32::msi::Database::CreationFailed());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (w32::msi::Database::InvalidParameter());
            }
            else if ( result == ERROR_OPEN_FAILED ) {
                throw (w32::msi::Database::OpeningFailed());
            }
            UNCHECKED_INSTALLER_ERROR(MsiOpenDatabase,result);
        }
        return (value);
    }

}

namespace w32 { namespace msi {

    const Database::Mode Database::Mode::readonly ()
    {
        return (reinterpret_cast<::LPCWSTR>(MSIDBOPEN_READONLY));
    }

    const Database::Mode Database::Mode::transaction ()
    {
        return (reinterpret_cast<::LPCWSTR>(MSIDBOPEN_TRANSACT));
    }

    const Database::Mode Database::Mode::direct ()
    {
        return (reinterpret_cast<::LPCWSTR>(MSIDBOPEN_DIRECT));
    }

    const Database::Mode Database::Mode::create ()
    {
        return (reinterpret_cast<::LPCWSTR>(MSIDBOPEN_CREATE));
    }

    const Database::Mode Database::Mode::createdirect ()
    {
        return (reinterpret_cast<::LPCWSTR>(MSIDBOPEN_CREATEDIRECT));
    }

    Database::Mode::Mode ( Value value )
        : myValue(value)
    {
    }

    Database::Mode::Value Database::Mode::value () const
    {
        return (myValue);
    }

    const Database::State Database::State::read ()
    {
        return (MSIDBSTATE_READ);
    }

    const Database::State Database::State::write ()
    {
        return (MSIDBSTATE_WRITE);
    }

    const Database::State Database::State::error ()
    {
        return (MSIDBSTATE_ERROR);
    }

    Database::State::State ( Value value )
        : myValue(value)
    {
    }

    Database::State::Value Database::State::value () const
    {
        return (myValue);
    }

    bool Database::State::operator== ( const State& other ) const
    {
        return (myValue == other.myValue);
    }

    bool Database::State::operator!= ( const State& other ) const
    {
        return (myValue != other.myValue);
    }

    Database::State Database::State::of ( const Database& database )
    {
        return (State(::MsiGetDatabaseState(database.handle())));
    }

    Database::Database ( const Handle& handle )
        : Object(handle), myMode(Mode::direct())
    {
    }

    Database::Database ( const string& path, const Mode& mode )
        : Object(claim(::open(path.c_str(), mode.value()))), myMode(mode)
    {
    }

    Database::Mode Database::mode () const
    {
        return (myMode);
    }

    Database::State Database::state () const
    {
        return (State::of(*this));
    }

    void Database::commit ()
    {
        const ::UINT result = ::MsiDatabaseCommit(handle());
        if ( result != ERROR_SUCCESS ) {
            UNCHECKED_INSTALLER_ERROR(MsiOpenDatabase,result);
        }
    }

    void Database::export_ (
        const char * table, const char * folder, const char * file
        )
    {
        const ::UINT result = ::MsiDatabaseExport(
            handle(), table, folder, file
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_BAD_PATHNAME ) {
                throw (BadPathName());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiDatabaseExport,result);
        }
    }

    void Database::import ( const char * folder, const char * file )
    {
        const ::UINT result = ::MsiDatabaseImport(handle(),folder,file);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_BAD_PATHNAME ) {
                throw (BadPathName());
            }
            else if ( result == ERROR_FUNCTION_FAILED ) {
                throw (FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiDatabaseImport,result);
        }
    }

    void Database::merge ( const Database& other, const char * table )
    {
        const ::UINT result = ::MsiDatabaseMerge(
            handle(), other.handle(), table
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_FUNCTION_FAILED ) {
                throw (FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_TABLE ) {
                throw (InvalidTable());
            }
            else if ( result == ERROR_DATATYPE_MISMATCH ) {
                throw (DatatypeMismatch());
            }
            UNCHECKED_INSTALLER_ERROR(MsiDatabaseMerge,result);
        }
    }

} }
