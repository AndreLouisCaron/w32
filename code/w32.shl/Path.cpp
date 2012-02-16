// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
