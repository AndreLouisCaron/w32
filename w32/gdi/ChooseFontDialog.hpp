#ifndef _win32c_gdi_ChooseFontDialog_hpp__
#define _win32c_gdi_ChooseFontDialog_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <win32c/NotCopyable.hpp>
#include <Windows.h>
#include <CDerror.h>

namespace win32c { namespace gdi {

    class ChooseFontDialog :
        private NotCopyable
    {
        /* data. */
    private:
        ::CHOOSEFONT myData;

        /* construction. */
    private:
            // Not designed/coded yet.
        ChooseFontDialog ();

        /* methods. */
    public:
        bool prompt ()
        {
            ::BOOL result = ::ChooseFont(&myData);
            if ( result == 0 )
            {
                const ::DWORD error = ::CommDlgExtendedError();
                if ( error == 0 ) {
                    return (false);
                }
                // problem!.
            }
            return (true);
        }
    };

} }

#endif /* _win32c_gdi_ChooseFontDialog_hpp__ */
