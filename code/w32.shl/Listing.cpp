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

#include <w32.shl/Listing.hpp>
#include <w32.shl/Item.hpp>

namespace {

    ::IEnumShellItems * create ( ::IShellItem * item )
    {
        const w32::com::Guid& I = w32::com::guidof< ::IEnumShellItems >();
        ::IEnumShellItems * listing = 0;
        const w32::com::Result result =
            item->BindToHandler(0, BHID_StorageEnum, I, (void**)&listing);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IShellFolder, BindToHandler, result);
        }
        return (listing);
    }

}

namespace w32 { namespace shl {

    Listing::Listing ( ::IEnumShellItems * object )
        : com::Wrapper< ::IEnumShellItems >(object)
    {
    }

    Listing::Listing ( const Item& item )
        : com::Wrapper< ::IEnumShellItems >( ::create(item.ptr().value()) )
    {
    }

    Listing Listing::clone () const
    {
        ::IEnumShellItems * clone = 0;
        const com::Result result = ptr()->Clone(&clone);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Clone, result);
        }
        return (Listing(clone));
    }

    void Listing::reset () const
    {
        const com::Result result = ptr()->Reset();
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Reset, result);
        }
    }

    void Listing::skip ( size_type count ) const
    {
        const com::Result result = ptr()->Skip(count);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Skip, result);
        }
    }

    bool Listing::next ( Item& next )
    {
        ::IShellItem * item = 0;
        const com::Result result = ptr()->Next(1, &item, 0);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IEnumShellItems, Next, result);
        }
        if ( result == w32::com::Result::false_() ) {
            return (false);
        }
        next = Item(item);
        return (true);
    }

} }
