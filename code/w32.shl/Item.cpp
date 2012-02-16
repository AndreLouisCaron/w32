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

#include <w32.shl/Item.hpp>
#include <w32.shl/Attributes.hpp>
#include <w32.shl/Folder.hpp>
#include <w32.shl/Location.hpp>
#include <w32.shl/Path.hpp>
#include <ntquery.h>

namespace {

    ::IShellItem * open ( ::LPCITEMIDLIST path )
    {
        ::IShellItem * item = 0;
        const w32::com::Result result =
            ::SHCreateShellItem(0, 0, path, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, SHCreateShellItem, result);
        }
        return (item);
    }

    ::IShellItem * open ( ::IShellFolder * parent, ::LPCITEMIDLIST path )
    {
        ::IShellItem * item = 0;
        const w32::com::Result result =
            ::SHCreateShellItem(0, parent, path, &item);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(none, SHCreateShellItem, result);
        }
        return (item);
    }

}

namespace w32 { namespace shl {

    Item::Item ( ::IShellItem * object )
        : com::Wrapper< ::IShellItem >(object)
    {
    }

    Item::Item ( const Path& path )
        : com::Wrapper< ::IShellItem >( ::open(path.backend()) )
    {
    }

    Item::Item ( const Folder& parent, const Path& path )
        : com::Wrapper< ::IShellItem >(
              ::open(parent.ptr().value(), path.backend()) )
    {
    }

    Item Item::parent () const
    {
        ::IShellItem * parent = 0;
        const com::Result result = ptr()->GetParent(&parent);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetParent, result);
        }
        return (Item(parent));
    }

    string Item::name () const
    {
        const ::SIGDN format = SIGDN_NORMALDISPLAY;
        wchar_t * name = 0;
        const com::Result result = ptr()->GetDisplayName(format, &name);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetDisplayName, result);
        }
        const string value(name);
        //com::free(name);
        return (value);
    }

    Attributes Item::attributes () const
    {
        return (attributes(Attributes::all()));
    }

    Attributes Item::attributes ( Attributes mask ) const
    {
        return (Attributes::of(*this, mask));
    }

    int Item::compare ( const Item& rhs ) const
    {
        const ::SICHINTF hint = SICHINT_ALLFIELDS;
        int order = 0;
        const com::Result result =
            ptr()->Compare(rhs.ptr().value(), hint, &order);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, Compare, result);
        }
        return (order);
    }

    bool Item::operator== ( const Item& rhs ) const
    {
        return (this->compare(rhs) == 0);
    }

    bool Item::operator!= ( const Item& rhs ) const
    {
        return (this->compare(rhs) != 0);
    }

    Item root ()
    {
        return (Location::desktop());
    }

    Path abspath ( const Item& item )
    {
        const Item parent = item.parent();
        const Folder folder(parent);
        const string name = item.name();
        try {
            const Path last = folder.path(name);
            return (Path(abspath(parent), folder.path(name)));
        }
            // todo: stop on something better than an exception!
        catch ( ... ) {}
        return (Path());
    }

    Item2::Item2 ( ::IShellItem2 * object )
        : com::Wrapper< ::IShellItem2 >(object)
    {
    }

    Item2::Item2 ( const Item& item )
        : com::Wrapper< ::IShellItem2 >
              ( com::cast< ::IShellItem2 >(item.ptr().value()) )
    {
    }

    qword Item2::size () const
    {
        const ::GUID storage = { 0xB725F130, 0x47EF, 0x101A,
            0xA5, 0xF1, 0x02, 0x60, 0x8C, 0x9E, 0xEB, 0xAC};
        const ::SHCOLUMNID PKEY_Size = {storage, PID_STG_SIZE};
        ::ULONGLONG size = 0;
        const com::Result result = ptr()->GetUInt64(PKEY_Size, &size);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem2, GetUInt64, result);
        }
        return (size);
    }

} }
