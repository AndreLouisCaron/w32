#ifndef _stdc_InputFile_hpp__
#define _stdc_InputFile_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Error.hpp"
#include <cstdio>

namespace stdc {

    class InputFile
    {
        /* data. */
    private:
        ::FILE *const myHandle;

        /* construction. */
    public:
        InputFile ( const char * path )
            : myHandle(::fopen(path, "rb"))
        {
            if ( myHandle == 0 ) {
                STDC_ERROR(fopen);
            }
        }

        InputFile ( const wchar_t * path )
            : myHandle(::_wfopen(path, L"rb"))
        {
            if ( myHandle == 0 ) {
                STDC_ERROR(wfopen);
            }
        }

    private:
        InputFile ( const InputFile& );

    public:
        ~InputFile ()
        {
            if ( ::fclose(myHandle) != 0 ) {
                STDC_ERROR(fclose);
            }
        }

        /* methods. */
    public:
        ::FILE * handle () const
        {
            return (myHandle);
        }

        /* operators. */
    private:
        InputFile& operator= ( const InputFile& );
    };

}

#endif /* _stdc_InputFile_hpp__ */
