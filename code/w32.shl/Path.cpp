// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32.shl/Path.hpp>
#include <w32/Error.hpp>

namespace w32 { namespace shl {

    Path::Path ()
        : myBackend(0)
    {
    }

    Path::Path ( ::LPCITEMIDLIST list )
        : myBackend(ILClone(list))
    {
    }

    Path::Path ( const Path& list )
        : myBackend(ILClone(list.backend()))
    {
    }

    Path::Path ( const string& path )
        : myBackend(::ILCreateFromPathW(path.data()))
    {
    }

    Path::Path ( ::LPCITEMIDLIST parent, ::LPCITEMIDLIST child )
        : myBackend(ILCombine(parent,child))
    {
    }

    Path::Path ( const Path& parent, const Path& child )
        : myBackend(ILCombine(parent.backend(),child.backend()))
    {
    }

    Path::Path ( const void * data, const size_type size )
        : myBackend((::ITEMIDLIST*)SHAlloc(2+size))
    {
        std::memcpy(myBackend->mkid.abID,data,size);
    }

    Path::~Path ()
    {
        if ( myBackend != 0 ) {
            ::ILFree(myBackend);
        }
    }

    ::LPCITEMIDLIST Path::backend () const
    {
        return (myBackend);
    }

    ::LPITEMIDLIST Path::release ()
    {
        const ::LPITEMIDLIST backend = myBackend;
        myBackend = 0;
        return (backend);
    }

    void Path::swap ( Path& other )
    {
        const ::LPITEMIDLIST temporary = myBackend;
        myBackend = other.myBackend;
        other.myBackend = temporary;
    }

    Path::size_type Path::size () const
    {
        return (ILGetSize(myBackend));
    }

    bool Path::empty () const
    {
        return (ILIsEmpty(myBackend));
    }

    Path::size_type Path::components() const
    {
        size_type count = 0;
        if ( myBackend != 0 )
        {
            ::LPCITEMIDLIST current = myBackend;
            while ( current->mkid.cb > 0 ) {
                ++count, current = ILNext(current);
            }
        }
        return (count);
    }

    Path::iterator Path::begin () const
    {
        return (iterator(myBackend));
    }

    Path::iterator Path::end () const
    {
        return (iterator(ILNext(ILFindLastID(myBackend))));
    }

    void Path::pop ()
    {
        const ::BOOL result = ::ILRemoveLastID(myBackend);
        if ( result == 0 ) {
            UNCHECKED_WIN32C_ERROR(ILRemoveLastID, 0);
        }
    }

    Path& Path::operator= ( const Path& other )
    {
        Path(other).swap(*this);
        return (*this);
    }

    Path& Path::operator= ( ::LPCITEMIDLIST other )
    {
        Path(other).swap(*this);
        return (*this);
    }

    Path::operator bool () const
    {
        return (backend() != 0);
    }

    bool Path::operator! () const
    {
        return (backend() == 0);
    }

    Path::operator string () const
    {
        wchar_t buffer[MAX_PATH];
        if ( ::SHGetPathFromIDListW(backend(), buffer) == FALSE )
        {
                // This function is documented to fail only if the list is
                // invalid or the target is a virtual object and does not
                // map to the filesystem.
            const ::DWORD error = ERROR_FILE_NOT_FOUND;
            UNCHECKED_WIN32C_ERROR(SHGetPathFromIDList, error);
        }
        return (buffer);
    }

    bool operator== ( const Path& lhs, const Path& rhs )
    {
        return (ILIsEqual(lhs.backend(),rhs.backend()) != FALSE);
    }

    bool operator!= ( const Path& lhs, const Path& rhs )
    {
        return (ILIsEqual(lhs.backend(),rhs.backend()) == FALSE);
    }

} }
