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

#include <w32.shl/Stream.hpp>
#include <w32.shl/Binding.hpp>
#include <w32.shl/Item.hpp>
#include <w32.shl/Path.hpp>
#include <w32.shl/Stat.hpp>
#include <iostream>

namespace {

    ::IStream * cast ( ::IShellItem * item )
    {
            // Ask for object in readonly mode.
        w32::shl::Binding binding;
        /*w32::shl::Binding::Options options = binding.options();
        options.access(STGM_READ|STGM_SHARE_DENY_WRITE);
        binding.options(options);*/
        
            // Open it.
        const w32::com::Guid I = w32::com::guidof< ::IStream >();
        ::IStream * stream = 0;
        const w32::com::Result result = item->BindToHandler
            (binding.ptr().value(), BHID_Stream, I, (void**)&stream);
        if ( result.bad() ) {
            std::cout << "Couldn't open stream!" << std::endl;
            UNCHECKED_COM_ERROR(IShellItem, BindToHandler, result);
        }
        return (stream);
    }

}

namespace w32 { namespace shl {

    Stream Stream::open ( const shl::Path& path )
    {
        ::IStream * stream = 0;
        const com::Result result = ::SHCreateItemFromIDList
            (path.backend(), IID_IStream, reinterpret_cast<void**>(&stream));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(void, SHCreateItemFromIDList, result);
        }
        Stream wrapper(stream);
        return (wrapper);
    }

    Stream::Stream ( const Ptr& backend )
        : Wrapper< ::IStream >(backend)
    {
    }

    Stream::Stream ( const Item& item )
        : Wrapper< ::IStream >( ::cast(item.ptr().value()) )
    {
    }

    ulong Stream::read ( void * buffer, ulong bytes )
    {
        ::ULONG read = 0;
        const com::Result result = ptr()->Read(buffer, bytes, &read);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IStream, Read, result);
        }
        return (read);
    }

    ulong Stream::write ( const void * buffer, ulong bytes )
    {
        ::ULONG written = 0;
        const com::Result result = ptr()->Write(buffer, bytes, &written);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IStream, Write, result);
        }
        return (written);
    }

    void Stream::stat ( Stat& info ) const
    {
        info.clear();
        const com::Result result = ptr()->Stat(&info.data(), STATFLAG_DEFAULT);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IStream, Stat, result);
        }
    }

} }
