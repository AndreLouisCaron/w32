// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.in/Session.hpp>
#include <w32.in/IStream.hpp>
#include <w32/Error.hpp>

namespace {

    ::HINTERNET establish ( ::LPCWSTR agent )
    {
        const ::DWORD access = INTERNET_OPEN_TYPE_DIRECT;
        const ::DWORD flags = 0; // INTERNET_FLAG_ASYNC, INTERNET_FLAG_OFFLINE;
        const ::HINTERNET result = ::InternetOpenW
            (agent, access, 0, 0, flags);
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetOpen, error);
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

    const Session::Handle Session::claim ( ::HINTERNET object )
    {
        return (Handle(object, &::destroy));
    }

    const Session::Handle Session::proxy ( ::HINTERNET object )
    {
        return (Handle(object, &::abandon));
    }

    Session::Session ( const string& agent )
        : myHandle(claim( ::establish(agent.c_str()) ))
    {
    }

    const Session::Handle& Session::handle () const
    {
        return (myHandle);
    }

    IStream Session::open ( const string& url )
    {
        return (IStream(*this, url));
    }

} }
