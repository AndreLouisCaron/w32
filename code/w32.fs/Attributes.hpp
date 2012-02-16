#ifndef _w32_fs_Attributes_hpp__
#define _w32_fs_Attributes_hpp__

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

namespace w32 { namespace fs {

    /*!
     * @ingroup w32-fs
     * @brief File attributes.
     */
    class Attributes
    {
        /* data. */
    private:
        dword myFlags;

        /* construction. */
    public:
        explicit Attributes ( const dword& flags );
        explicit Attributes ( const string& path );

        /* methods. */
    public:
        const dword & flags () const;
        bool invalid () const;
        bool archive () const;
        bool compressed () const;
        bool folder () const;
        bool encrypted () const;
        bool hidden () const;
        bool normal () const;
        bool offline () const;
        bool readonly () const;
        bool reparsepoint () const;
        bool sparse () const;
        bool system () const;
        bool temporary () const;

        /* operators. */
    public:
        bool operator== ( const Attributes& other ) const;
        bool operator!= ( const Attributes& other ) const;
    };

    bool exists ( const string& path );

} }

#endif /* _w32_fs_Attributes_hpp__ */
