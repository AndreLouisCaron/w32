// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/fs/Attributes.hpp>

namespace w32 { namespace fs {

    Attributes::Attributes ( const ::DWORD& flags )
        : myFlags(flags)
    {
    }

    Attributes::Attributes ( const string& path )
        : myFlags(::GetFileAttributesW(path.c_str()))
    {
    }

    const ::DWORD & Attributes::flags () const
    {
        return (myFlags);
    }

    bool Attributes::invalid () const
    {
        return (myFlags == INVALID_FILE_ATTRIBUTES);
    }

    bool Attributes::archive () const
    {
        return ((myFlags & FILE_ATTRIBUTE_ARCHIVE) != 0);
    }

    bool Attributes::compressed () const
    {
        return ((myFlags & FILE_ATTRIBUTE_COMPRESSED) != 0);
    }

    bool Attributes::folder () const
    {
        return ((myFlags & FILE_ATTRIBUTE_DIRECTORY) != 0);
    }

    bool Attributes::encrypted () const
    {
        return ((myFlags & FILE_ATTRIBUTE_ENCRYPTED) != 0);
    }

    bool Attributes::hidden () const
    {
        return ((myFlags & FILE_ATTRIBUTE_HIDDEN) != 0);
    }

    bool Attributes::normal () const
    {
        return ((myFlags & FILE_ATTRIBUTE_NORMAL) != 0);
    }

    bool Attributes::offline () const
    {
        return ((myFlags & FILE_ATTRIBUTE_OFFLINE) != 0);
    }

    bool Attributes::readonly () const
    {
        return ((myFlags & FILE_ATTRIBUTE_READONLY) != 0);
    }

    bool Attributes::reparsepoint () const
    {
        return ((myFlags & FILE_ATTRIBUTE_REPARSE_POINT) != 0);
    }

    bool Attributes::sparse () const
    {
        return ((myFlags & FILE_ATTRIBUTE_SPARSE_FILE) != 0);
    }

    bool Attributes::system () const
    {
        return ((myFlags & FILE_ATTRIBUTE_SYSTEM) != 0);
    }

    bool Attributes::temporary () const
    {
        return ((myFlags & FILE_ATTRIBUTE_TEMPORARY) != 0);
    }

    bool Attributes::operator== ( const Attributes& other ) const
    {
        return (myFlags == other.myFlags);
    }

    bool Attributes::operator!= ( const Attributes& other ) const
    {
        return (myFlags != other.myFlags);
    }

    bool exists ( const string& path )
    {
        const Attributes attributes(path);
        return (!attributes.invalid());
    }

} }
