#ifndef _w32_sy_Token_hpp__
#define _w32_sy_Token_hpp__

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
#include <w32/Object.hpp>
#include <w32/types.hpp>

namespace w32 { namespace ipc {

    class Process;

} }

namespace w32 { namespace sy {

    class ImpersonationLevel;

    class Token :
        public Object
    {
        /* nested types. */
    public:
        class Type;
        class Access;

        /* class methods. */
    public:
        static Token of ( const ipc::Process& process );

        /* construction. */
    public:
        explicit Token ( const Handle& handle );

        Token ( const Token& token, const ImpersonationLevel& level );

        /* methods. */
    public:
        bool restricted () const;
    };

    class Token::Type
    {
        /* class data. */
    public:
        static const Type primary ();
        static const Type impersonation ();

        /* nested types. */
    public:
        typedef ::TOKEN_TYPE Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* class methods. */
    public:
        static Type of ( const Token& token );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const Type& other ) const;
        bool operator!= ( const Type& other ) const;
    };

    class Token::Access
    {
        /* class data. */
    public:
        static const Access adjustdefault ();
        static const Access adjustgroups ();
        static const Access adjustprivileges ();
        static const Access adjustsession ();
        static const Access assignprimary ();
        static const Access duplicate ();
        static const Access execute ();
        static const Access impersonate ();
        static const Access query ();
        static const Access querysource ();
        static const Access read ();
        static const Access write ();
        static const Access all ();
        static const Access none ();

        /* nested types. */
    public:
        typedef dword Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Access ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const Access& other ) const;
        bool operator!= ( const Access& other ) const;
        Access operator| ( const Access& other ) const;
        Access& operator|= ( const Access& other );
        Access operator& ( const Access& other ) const;
        Access& operator&= ( const Access& other );
    };

} }

#endif /* _w32_sy_Token_hpp__ */
