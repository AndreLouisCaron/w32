#ifndef _w32_fs_Time_hpp__
#define _w32_fs_Time_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Time.hpp>

namespace w32 { namespace fs {

    class W32_FS_EXPORT Time
    {
        /* nested types. */
    public:
        typedef ::FILETIME Data;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Time ();
        Time ( const Data& value );
        Time ( const ::SYSTEMTIME& value );
        Time ( const w32::Time& value );

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
        dword low () const;
        dword high () const;

        /* operators. */
    public:
        operator w32::Time () const;
    };

} }

#endif /* _w32_fs_Time_hpp__ */
