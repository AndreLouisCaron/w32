#ifndef _ring_hpp__
#define _ring_hpp__

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

#include <w32/NotCopyable.hpp>
#include <cstddef>

namespace server {

    class ring :
        private w32::NotCopyable
    {
        /* nested types. */
    public:
        typedef unsigned char byte;

        /* data. */
    private:
        byte* myLPtr; byte* myUPtr;
        byte* myGPtr; byte* myPPtr;

        /* construction. */
    public:
        ring ( byte* lptr, byte* uptr );

        /* methods. */
    public:
        std::size_t size () const;
        std::size_t capacity () const;
        bool empty () const;
        bool full () const;

        byte * put ( byte * lower, byte * upper );
        const byte * put ( const byte * lower, const byte * upper );
        byte * get ( byte * lower, byte * upper );
        std::size_t peek ( byte item ) const;

            // Convenient overloads.
        std::size_t put ( byte * data, std::size_t size );
        std::size_t get ( byte * data, std::size_t size );
        std::size_t put ( void * data, std::size_t size );
        std::size_t get ( void * data, std::size_t size );
    };

}

#endif /* _ring_hpp__ */
