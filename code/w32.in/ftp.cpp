// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.in/ftp.hpp>
#include <w32.in/Session.hpp>
#include <w32.in/Url.hpp>
#include <w32.fs/Attributes.hpp>
#include <w32.fs/Time.hpp>
#include <w32/Error.hpp>

namespace {

    ::HINTERNET establish ( ::HINTERNET session, const w32::in::Url& url )
    {
        const ::HANDLE result = ::InternetConnectW(
            session, url.host().data(), url.port(), url.username().data(),
            url.password().data(), INTERNET_SERVICE_FTP, 0, 0
            );
        if ( result == NULL )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetConnect, error);
        }
        return (result);
    }

    ::HINTERNET establish ( ::HINTERNET session, const w32::string& url )
    {
        return (establish(session, w32::in::Url(url)));
    }

    ::HINTERNET find ( ::HINTERNET connection, ::LPWIN32_FIND_DATAW entry )
    {
        const ::HINTERNET result =
            ::FtpFindFirstFileW(connection, 0, entry, 0, 0);
        if ( result == NULL )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FtpFindFirstFile, error);
        }
        return (result);
    }

    void abandon ( ::HINTERNET object ) {}
    void destroy ( ::HINTERNET object )
    {
        const ::BOOL result = ::InternetCloseHandle(object);
        if ( result == FALSE )
        {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace in { namespace ftp {

    Connection::Connection ( Session& session, const string& url )
        : in::Connection(Handle(claim( ::establish(session.handle(), url) )))
    {
    }

    string Connection::path () const
    {
        ::DWORD size = 0;
        { // fetch path size.
            const ::BOOL result =
                ::FtpGetCurrentDirectoryW(handle(), 0, &size);
            if ( result == FALSE )
            {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FtpFindFirstFile, error);
            }
        }
        
        string path(size);
        const ::BOOL result =
            ::FtpGetCurrentDirectoryW(handle(), path.data(), &size);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FtpGetCurrentDirectory, error);
        }
        return (path);
    }

    void Connection::path ( const string& path )
    {
        const ::BOOL result = ::FtpSetCurrentDirectoryW(handle(), path.data());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(FtpSetCurrentDirectory, error);
        }
    }

    qword Connection::size ( const string& file )
    {
        ::LARGE_INTEGER size;
        size.LowPart = ::FtpGetFileSize(handle(),
            reinterpret_cast<::DWORD*>(&size.HighPart));
        return (size.QuadPart);
    }

    const Listing::Handle Listing::claim ( ::HANDLE object )
    {
        return (Handle(object, &::destroy));
    }

    const Listing::Handle Listing::proxy ( ::HANDLE object )
    {
        return (Handle(object, &::abandon));
    }

    Listing::Listing ( Connection& connection, Result& result )
        : myHandle(claim( ::find(connection.handle(), &result.data()) ))
    {
    }

    const Listing::Handle& Listing::handle () const
    {
        return (myHandle);
    }

    bool Listing::next ( Result& result )
    {
        const ::BOOL status = ::InternetFindNextFileW(handle(),&result.data());
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

    Listing::Result::Result ()
    {
        ::ZeroMemory(&myData,sizeof(myData));
    }

    Listing::Result::Data& Listing::Result::data ()
    {
        return (myData);
    }

    const Listing::Result::Data& Listing::Result::data () const
    {
        return (myData);
    }

    string Listing::Result::name () const
    {
        return (myData.cFileName);
    }

    fs::Attributes Listing::Result::attributes () const
    {
        return (fs::Attributes(myData.dwFileAttributes));
    }

    fs::Time Listing::Result::creation () const
    {
        return (fs::Time(myData.ftCreationTime));
    }

    fs::Time Listing::Result::access () const
    {
        return (fs::Time(myData.ftLastAccessTime));
    }

    fs::Time Listing::Result::modification () const
    {
        return (fs::Time(myData.ftLastWriteTime));
    }

    qword Listing::Result::size () const
    {
        return ((qword(myData.nFileSizeHigh)<<32)|qword(myData.nFileSizeLow));
    }

} } }
