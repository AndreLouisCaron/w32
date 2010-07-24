#ifndef _win32c_gdi_ChooseColorDialog_hpp__
#define _win32c_gdi_ChooseColorDialog_hpp__

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

    class ChooseColorDialog :
        private NotCopyable
    {
        /* data. */
    private:
        ::CHOOSECOLOR myData;

        /* construction. */
    private:
            // Not designed/coded yet.
        ChooseColorDialog ();

        /* methods. */
    public:
        bool prompt ()
        {
            ::BOOL result = ::ChooseColor(&myData);
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

#endif /* _win32c_gdi_ChooseColorDialog_hpp__ */
