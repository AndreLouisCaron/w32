// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Stream.hpp>
#include <w32/shl/Binding.hpp>
#include <w32/shl/Item.hpp>
#include <w32/shl/Path.hpp>
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
    };

    ulong Stream::write ( const void * buffer, ulong bytes )
    {
        ::ULONG written = 0;
        const com::Result result = ptr()->Write(buffer, bytes, &written);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IStream, Write, result);
        }
        return (written);
    };

} }
