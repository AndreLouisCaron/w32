#ifndef _w32_fs_Attributes_hpp__
#define _w32_fs_Attributes_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/string.hpp>

namespace w32 { namespace fs {

    class W32_FS_EXPORT Attributes
    {
        /* data. */
    private:
        dword myFlags;

        /* construction. */
    public:
        explicit Attributes ( const dword& flags );
        explicit Attributes ( const string& path );

        /* methods. */
    public:
        const dword & flags () const;
        bool invalid () const;
        bool archive () const;
        bool compressed () const;
        bool folder () const;
        bool encrypted () const;
        bool hidden () const;
        bool normal () const;
        bool offline () const;
        bool readonly () const;
        bool reparsepoint () const;
        bool sparse () const;
        bool system () const;
        bool temporary () const;

        /* operators. */
    public:
        bool operator== ( const Attributes& other ) const;
        bool operator!= ( const Attributes& other ) const;
    };

    bool W32_FS_EXPORT exists ( const string& path );

} }

#endif /* _w32_fs_Attributes_hpp__ */
