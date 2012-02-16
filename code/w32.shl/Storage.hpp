#ifndef _w32_shl_Storage_hpp__
#define _w32_shl_Storage_hpp__

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

#include "__configure__.hpp"
#include <w32.com/Wrapper.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace shl {

    class Folder;
    class Item;
    class Path;
    class Stat;
    class Stream;

    class Storage :
        public com::Wrapper< ::IStorage >
    {
        /* nested types. */
    public:
        class Listing;

        /* construction. */
    public:
        explicit Storage ( ::IStorage * object );
        explicit Storage ( const com::Ptr< ::IStorage >& object );
        explicit Storage ( const Item& item );
        Storage ( const Folder& folder, const Path& path );

        /* methods. */
    public:
        Stream open ( const string& child ) const;
        Stream create ( const string& child );
        void destroy ( const string& child );
        void rename ( const string& from, const string& to );
        void stat ( Stat& info ) const;
        Storage branch ( const string& child );
    };

    class Storage::Listing :
        public com::Wrapper< ::IEnumSTATSTG >
    {
        /* nested types. */
    public:
        typedef ulong size_type;

        /* construction. */
    public:
        explicit Listing ( ::IEnumSTATSTG * object );
        Listing ( const Storage& storage );

        /* methods. */
    public:
        Listing clone () const;
        void reset ();
        bool next ( Stat& item );
        void skip ( size_type count );
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IStorage > ()
{
    return (IID_IStorage);
}

#endif /* _w32_shl_Storage_hpp__ */
