#ifndef _w32_shl_Folder_hpp__
#define _w32_shl_Folder_hpp__

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

    class Item;
    class Path;
    class Stream;

    class Folder :
        public com::Wrapper< ::IShellFolder >
    {
        /* nested types. */
    public:
        class Listing;

        /* construction. */
    public:
        explicit Folder ( ::IShellFolder * object );
        explicit Folder ( com::Ptr< ::IShellFolder > object );
        explicit Folder ( const Item& item );
        explicit Folder ( const Folder& parent, const Path& name );

        /* methods. */
    public:
        Stream open ( const Path& path ) const;
        Path path ( const string& item ) const;
        Item child ( const Path& path ) const;
    };

    class Folder2 :
        public com::Wrapper< ::IShellFolder2 >
    {
        /* construction. */
    public:
        explicit Folder2 ( ::IShellFolder2 * object );
        Folder2 ( const Folder& folder );

        /* methods. */
    public:
        qword size ( const Path& path ) const;
    };

    class Folder::Listing :
        public com::Wrapper< ::IEnumIDList >
    {
        /* nested types. */
    public:
        typedef ulong size_type;

        /* construction. */
    public:
        explicit Listing ( ::IEnumIDList * object );
        Listing ( const Folder& folder );

        /* methods. */
    public:
        Listing clone () const;
        void reset () const;
        bool next ( Path& next );
        void skip ( size_type count ) const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder > ()
{
    return (IID_IShellFolder);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder2 > ()
{
    return (IID_IShellFolder2);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IEnumIDList > ()
{
    return (IID_IEnumIDList);
}

#endif /* _w32_shl_Folder_hpp__ */
