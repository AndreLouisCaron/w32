#ifndef _stdc_OutputFile_hpp__
#define _stdc_OutputFile_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "Error.hpp"
#include <cstdio>
#include <cwchar>

namespace stdc {

    class OutputFile
    {
        /* data. */
    private:
        ::FILE *const myHandle;

        /* construction. */
    public:
        OutputFile ( const char * path )
            : myHandle(::fopen(path, "wb"))
        {
            if ( myHandle == 0 ) {
                STDC_ERROR(fopen);
            }
        }

        OutputFile ( const wchar_t * path )
            : myHandle(::_wfopen(path, L"wb"))
        {
            if ( myHandle == 0 ) {
                STDC_ERROR(wfopen);
            }
        }

    private:
        OutputFile ( const OutputFile& );

    public:
        ~OutputFile ()
        {
            ::fclose(myHandle);
        }

        /* methods. */
    public:
        ::FILE * handle () const
        {
            return (myHandle);
        }

        /* operators. */
    private:
        OutputFile& operator= ( const OutputFile& );
    };

}

#endif /* _stdc_OutputFile_hpp__ */
