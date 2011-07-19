#ifndef _w32_msi_ErrorRecord_hpp__
#define _w32_msi_ErrorRecord_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/msi/Object.hpp>

namespace w32 { namespace msi {

    class ErrorRecord :
        public Object
    {
        /* construction. */
    public:
        ErrorRecord ();

        /* methods. */
    public:
        uint fields () const;
        int field ( uint index ) const;

#if 0
            // Something of the like...
        std::string field ( uint index ) const
        {
            char buffer[128];
            ::DWORD length = 128;
            return (::MsiRecordGetStringA(handle().get(),index,buffer,&length));
        }
#endif
    };

} }

#endif /* _w32_msi_ErrorRecord_hpp__ */
