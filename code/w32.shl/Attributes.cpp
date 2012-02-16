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

#include <w32.shl/Attributes.hpp>
#include <w32.shl/Item.hpp>
#include <w32.com/Error.hpp>

namespace w32 { namespace shl {

    const Attributes Attributes::copyable ()
    {
        return (SFGAO_CANCOPY);
    }

    const Attributes Attributes::moveable ()
    {
        return (SFGAO_CANMOVE);
    }

    const Attributes Attributes::linkable ()
    {
        return (SFGAO_CANLINK);
    }

    const Attributes Attributes::storable ()
    {
        return (SFGAO_STORAGE);
    }

    const Attributes Attributes::renamable ()
    {
        return (SFGAO_CANRENAME);
    }

    const Attributes Attributes::deletable ()
    {
        return (SFGAO_CANDELETE);
    }

    const Attributes Attributes::haspropsheet ()
    {
        return (SFGAO_HASPROPSHEET);
    }

    const Attributes Attributes::droptarget ()
    {
        return (SFGAO_DROPTARGET);
    }

    const Attributes Attributes::encrypted ()
    {
        return (SFGAO_ENCRYPTED);
    }

    const Attributes Attributes::slow ()
    {
        return (SFGAO_ISSLOW);
    }

    const Attributes Attributes::ghosted ()
    {
        return (SFGAO_GHOSTED);
    }

    const Attributes Attributes::link ()
    {
        return (SFGAO_LINK);
    }

    const Attributes Attributes::shared ()
    {
        return (SFGAO_SHARE);
    }

    const Attributes Attributes::readonly ()
    {
        return (SFGAO_READONLY);
    }

    const Attributes Attributes::hidden ()
    {
        return (SFGAO_HIDDEN);
    }

    const Attributes Attributes::stream ()
    {
        return (SFGAO_STREAM);
    }

    const Attributes Attributes::container ()
    {
        return (SFGAO_STORAGEANCESTOR);
    }

    const Attributes Attributes::removable ()
    {
        return (SFGAO_REMOVABLE);
    }

    const Attributes Attributes::compressed ()
    {
        return (SFGAO_COMPRESSED);
    }

    const Attributes Attributes::browsable ()
    {
        return (SFGAO_BROWSABLE);
    }

    const Attributes Attributes::folder ()
    {
        return (SFGAO_FOLDER);
    }

    const Attributes Attributes::filesystem ()
    {
        return (SFGAO_FILESYSTEM);
    }

    const Attributes Attributes::subfolders ()
    {
        return (SFGAO_HASSUBFOLDER);
    }

    const Attributes Attributes::all ()
    {
        return  (~::DWORD(0));
    }

    const Attributes Attributes::of ( const Item& item, Attributes mask )
    {
        ::SFGAOF attributes = 0;
        const com::Result result = item.ptr()->GetAttributes(mask, &attributes);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellItem, GetAttributes, result);
        }
        return (attributes);
    }

    Attributes::Attributes ( Value value )
        : myValue(value)
    {
    }

    Attributes::Value Attributes::value () const
    {
        return (myValue);
    }

    Attributes::operator Attributes::Value () const
    {
        return (myValue);
    }

    Attributes::operator bool () const
    {
        return (myValue != 0);
    }

    Attributes& Attributes::operator&= ( const Attributes& rhs )
    {
        myValue &= rhs.myValue; return (*this);
    }

    Attributes& Attributes::operator|= ( const Attributes& rhs )
    {
        myValue |= rhs.myValue; return (*this);
    }

    Attributes Attributes::operator& ( const Attributes& rhs ) const
    {
        Attributes result(*this); result &= rhs; return (result);
    }

    Attributes Attributes::operator| ( const Attributes& rhs ) const
    {
        Attributes result(*this); result |= rhs; return (result);
    }

} }
