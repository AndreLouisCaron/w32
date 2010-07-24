// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/Search.hpp>
#include <w32/Error.hpp>
#include <iostream>
#include <sstream>

namespace {

    ::HANDLE find ( ::LPCWSTR pattern, ::WIN32_FIND_DATAW& result )
    {
        const ::HANDLE handle = ::FindFirstFileW(pattern, &result);
        if ( handle == INVALID_HANDLE_VALUE ) {
            UNCHECKED_WIN32C_ERROR(FindFirstFile, ::GetLastError());
        }
        return (handle);
    }

    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::FindClose(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace fs {

    Search::Search ( const string& pattern, Result& result )
        : Object(claim(::find(pattern.data(), result.data())))
    {
    }

    bool Search::next ( Result& result )
    {
        const ::BOOL status = ::FindNextFileW(handle(),&result.data());
        if ( status == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            if ( error == ERROR_NO_MORE_FILES ) {
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(FindNextFile,error);
        }
        return (true);
    }

    Search::Result::Result ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    Search::Result::Data& Search::Result::data ()
    {
        return (myData);
    }

    const Search::Result::Data& Search::Result::data () const
    {
        return (myData);
    }

    string Search::Result::name () const
    {
        return (myData.cFileName);
    }

    Attributes Search::Result::attributes () const
    {
        return (Attributes(myData.dwFileAttributes));
    }

    Time Search::Result::creation () const
    {
        return (Time(myData.ftCreationTime));
    }

    Time Search::Result::access () const
    {
        return (Time(myData.ftLastAccessTime));
    }

    Time Search::Result::modification () const
    {
        return (Time(myData.ftLastWriteTime));
    }

    qword Search::Result::size () const
    {
        return ((qword(myData.nFileSizeHigh)<<32)|qword(myData.nFileSizeLow));
    }

} }
