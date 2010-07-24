// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include <w32/shl/Stream.hpp>

namespace w32 { namespace shl {

    Stream Stream::open ( const shl::Path& path )
    {
        ::IStream * stream = 0;
        const com::Result result = ::SHCreateItemFromIDList
            (path.backend(), IID_IStream, reinterpret_cast<void**>(&stream));
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(void, SHCreateItonFromIDList, result);
        }
        Stream wrapper(stream);
        return (wrapper);
    }

    Stream::Stream ( const Ptr& backend )
        : Wrapper< ::IStream >(backend)
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
