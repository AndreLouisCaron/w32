// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/in/check.hpp>
#include <w32/Error.hpp>

namespace {

    void perform ( ::LPCWSTR url, ::DWORD flags )
    {
        const ::BOOL result = ::InternetCheckConnectionW(url, flags, 0);
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(InternetCheckConnection, error);
        }
    }

}

namespace w32 { namespace in {

    void check ( bool force )
    {
        ::perform(0, force?FLAG_ICC_FORCE_CONNECTION:0);
    }

    void check ( const string& url, bool force )
    {
        ::perform(url.data(), force?FLAG_ICC_FORCE_CONNECTION:0);
    }

} }
