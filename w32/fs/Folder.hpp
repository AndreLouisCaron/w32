#ifndef _w32_fs_Folder_hpp__
#define _w32_fs_Folder_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/Transaction.hpp>
#include <w32/types.hpp>

namespace w32 { namespace fs {

    class W32_FS_EXPORT Folder :
        public Object
    {
        /* class methods. */
    public:
        static void create ( const string& path );
        static void create ( const string& path, Transaction& transaction );
        static void remove ( const string& path );
        static void remove ( const string& path, Transaction& transaction );
        static void current ( const string& path );
        static string current ();
        static bool is ( const string& path );

        /* construction. */
    public:
        explicit Folder ( const string& path );

    protected:
        Folder ( const string& path, dword attributes );

        /* methods. */
    public:
        string path () const;
    };

    class W32_FS_EXPORT ReparsePoint :
        public Folder
    {
        /* construction. */
    public:
        explicit ReparsePoint ( const string& path );
    };

} }

#endif /* _w32_fs_Folder_hpp__ */
