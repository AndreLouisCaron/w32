// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.in/IStream.hpp>
#include <w32.in/Session.hpp>
#include <w32/Error.hpp>

namespace {

    ::HINTERNET stream ( ::HINTERNET session, ::LPCWSTR url )
    {
        const ::HINTERNET result = ::InternetOpenUrlW
            (session, url, 0, 0, 0, 0);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetOpenUrl, error);
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

namespace w32 { namespace in {

    const IStream::Handle IStream::claim ( ::HINTERNET object )
    {
        return (Handle(object, &::destroy));
    }

    const IStream::Handle IStream::proxy ( ::HINTERNET object )
    {
        return (Handle(object, &::abandon));
    }

    IStream::IStream ( Session& session, const string& url )
        : myHandle(claim( ::stream(session.handle(), url.data()) ))
    {
    }

    const IStream::Handle& IStream::handle () const
    {
        return (myHandle);
    }

    dword IStream::get ( void * data, dword size )
    {
        ::DWORD got = 0;
        const ::BOOL result =
            ::InternetReadFile(handle(), data, size, &got);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetReadFile, error);
        }
        return (got);
    }

} }
