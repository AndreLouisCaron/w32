// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/msi/Record.hpp>
#include <w32/msi/Error.hpp>

namespace {

    ::MSIHANDLE create ( ::UINT fields )
    {
        ::MSIHANDLE handle = ::MsiCreateRecord(fields);
        if ( handle == 0 ) {
            throw (w32::msi::Record::CreationFailed());
        }
        return (handle);
    }

    ::MSIHANDLE fetch ( ::MSIHANDLE view )
    {
        ::MSIHANDLE handle = 0;
        const ::UINT result = ::MsiViewFetch(view,&handle);
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_NO_MORE_ITEMS ) {
                throw (w32::msi::View::NoMoreRecords());
            }
            else if ( result == ERROR_FUNCTION_FAILED ) {
                throw (w32::msi::View::FunctionFailed());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (w32::msi::View::InvalidHandle());
            }
            else if ( result == ERROR_INVALID_HANDLE_STATE ) {
                throw (w32::msi::View::InvalidState());
            }
            UNCHECKED_INSTALLER_ERROR(MsiViewFetch,result);
        }
        return (handle);
    }

    ::DWORD length ( ::MSIHANDLE record, ::UINT field )
    {
        char dummy[] = "";
        ::DWORD length = 0;
        const ::UINT result = ::MsiRecordGetStringA(record,field,dummy,&length);
        if ( result != ERROR_MORE_DATA )
        {
            if ( result == ERROR_INVALID_HANDLE ) {
                throw (w32::msi::Record::InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (w32::msi::Record::InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiRecordGetString,result);
        }
        return (length);
    }

}

namespace w32 { namespace msi {

    Record::Record ( View& view )
        : Object(claim(::fetch(view.handle()))), myField(1)
    {}

    Record::Record ( uint fields )
        : Object(claim(::create(fields))), myField(1)
    {
    }

    Record::Record ( const Handle& handle )
        : Object(handle), myField(1)
    {
    }

    bool Record::null ( uint field ) const
    {
        return (::MsiRecordIsNull(handle(),field+1) != FALSE);
    }

    uint Record::size ( uint field ) const
    {
        return (::MsiRecordDataSize(handle(),field+1));
    }

    uint Record::fields () const
    {
        return (::MsiRecordGetFieldCount(handle())-1);
    }

    void Record::clear ()
    {
        const uint result = ::MsiRecordClearData(handle());
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            UNCHECKED_INSTALLER_ERROR(MsiRecordClearData,result);
        }
    }

    int Record::integer ( uint field ) const
    {
        const int result = ::MsiRecordGetInteger(handle(),field+1);
        if ( result == MSI_NULL_INTEGER ) {
            throw (NullInteger());
        }
        return (result);
    }

    w32::string Record::string ( uint field ) const
    {
        ::DWORD size = length(handle(),field + 1) + 1;
        w32::string value(size,L'\0');
        
        const uint result = ::MsiRecordGetStringW(
            handle(), field + 1, const_cast<wchar_t*>(value.data()), &size
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
                // ERROR_MORE_DATA never occurs, we allocated enough space.
            UNCHECKED_INSTALLER_ERROR(MsiRecordGetString,result);
        }
        value.resize(value.size()-1);
        return (value);
    }

    Record& Record::operator<< ( int value )
    {
        const uint result = ::MsiRecordSetInteger(
            handle(), myField, value
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_FIELD ) {
                throw (InvalidField());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiRecordSetInteger,result);
        }
        ++myField;
        return (*this);
    }

    Record& Record::operator<< ( const std::string& value )
    {
        const uint result = ::MsiRecordSetStringA(
            handle(), myField, value.c_str()
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_FIELD ) {
                throw (InvalidField());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiRecordSetInteger,result);
        }
        ++myField;
        return (*this);
    }

    Record& Record::operator<< ( const std::wstring& value )
    {
        const uint result = ::MsiRecordSetStringW(
            handle(), myField, value.c_str()
            );
        if ( result != ERROR_SUCCESS )
        {
            if ( result == ERROR_INVALID_FIELD ) {
                throw (InvalidField());
            }
            else if ( result == ERROR_INVALID_HANDLE ) {
                throw (InvalidHandle());
            }
            else if ( result == ERROR_INVALID_PARAMETER ) {
                throw (InvalidParameter());
            }
            UNCHECKED_INSTALLER_ERROR(MsiRecordSetInteger,result);
        }
        ++myField;
        return (*this);
    }

} }
