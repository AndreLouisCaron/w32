#ifndef _w32_shl_Item_hpp__
#define _w32_shl_Item_hpp__

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
#include <w32/string.hpp>
#include <w32/types.hpp>
#include <w32.com/Wrapper.hpp>

namespace w32 { namespace shl {

    class Attributes;
    class Folder;
    class Path;

    class Item :
        public com::Wrapper< ::IShellItem >
    {
        /* construction. */
    public:
        explicit Item ( ::IShellItem * object );
        Item ( const Path& path );
        Item ( const Folder& folder, const Path& path );

        /* methods. */
    public:
        Item parent () const;
        string name () const;
        Attributes attributes () const;
        Attributes attributes ( Attributes mask ) const;
        int compare ( const Item& rhs ) const;

        /* operators. */
    public:
        bool operator== ( const Item& rhs ) const;
        bool operator!= ( const Item& rhs ) const;
    };

    Item root ();

    Path abspath ( const Item& item );

    class Item2 :
        public com::Wrapper< ::IShellItem2 >
    {
        /* construction. */
    public:
        explicit Item2 ( ::IShellItem2 * object );
        Item2 ( const Item& item );

        /* methods. */
    public:
        qword size () const;
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellItem > ()
{
    return (IID_IShellItem);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellItem2 > ()
{
    return (IID_IShellItem2);
}

#endif /* _w32_shl_Item_hpp__ */
