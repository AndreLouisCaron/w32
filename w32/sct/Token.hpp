#ifndef _w32_security_Token_hpp__
#define _w32_security_Token_hpp__

/*!
 * @file w32/sct/Token.hpp
 * @author Andre Caron
 */

#include "../__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/types.hpp>

namespace w32 { namespace sct {

        /*!
         * @brief Access token.
         */
    class Token :
        virtual public Object
    {
        /* nested types. */
    public:
        class Type
        {
            /* class data. */
        public:
            static const Type primary;
            static const Type impersonation;

            /* nested types. */
        public:
            typedef ::TOKEN_TYPE Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            explicit Type ( Value value );

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

        class Access
        {
            /* class data. */
        public:
            static const Access adjustdefault;
            static const Access adjustgroups;
            static const Access adjustprivileges;
            static const Access adjustsession;
            static const Access assignprimary;
            static const Access duplicate;
            static const Access execute;
            static const Access impersonate;
            static const Access query;
            static const Access querysource;
            static const Access read;
            static const Access write;
            static const Access all;
            static const Access none;

            /* nested types. */
        public:
            typedef dword Value;

            /* data. */
        private:
            Value myValue;

            /* construction. */
        private:
            explicit Access ( Value value );

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

        /* methods. */
    public:
        bool restricted () const;
    };

} }

#endif /* _w32_security_Token_hpp__ */
