#ifndef _w32_fs_File_hpp__
#define _w32_fs_File_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace fs {

    class File :
        public Object
    {
        /* nested types. */
    public:
        typedef qword size_type;
        class Access;

        /* class methods. */
    public:
        static void remove ( const string& path );
        static bool is ( const string& path );
        static bool compressed ( const string& path );
        static void encrypt ( const string& path );
        static void decrypt ( const string& path );
        static bool encrypted ( const string& path );
        static void prevent_encryption ( const string& path );

        /* construction. */
    public:
        explicit File ( const string& path );
        File ( const string& path, Access access );

        /* methods. */
    public:
        string path () const;
        void compress ();
        void decompress ();
        void sparsify ();
        size_type size () const;
    };

    class File::Access
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* values. */
    public:
        static Access i ();
        static Access o ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Access ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

} }

#endif /* _w32_fs_File_hpp__ */
