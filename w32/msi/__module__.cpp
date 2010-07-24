// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

    // Make sure header compiles standalone.
#include "__compiler__.hpp"
#include "__module__.hpp"
#include <w32.hpp>

namespace w32 {

        // Can't be "declspec(dllexport)"ed.
    std::locale::id Error::Put::id;

}

extern "C" {

    ::ULONG __stdcall DllMain (
        ::HINSTANCE instance, ::DWORD reason, ::LPVOID reserved
        )
    try
    {
        if ( reason == DLL_PROCESS_ATTACH )
        {
        }
        else if ( reason == DLL_PROCESS_DETACH )
        {
        }
        return (TRUE);
    }
    catch ( ... ) {
        return (FALSE);
    }

}
