#ifndef _w32_sy_Token_hpp__
#define _w32_sy_Token_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

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
