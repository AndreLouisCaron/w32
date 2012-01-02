#ifndef _w32_sy_ImpersonationLevel_hpp__
#define _w32_sy_ImpersonationLevel_hpp__

/*!
 * @file w32.sy/ImpersonationLevel.hpp
 * @author Andre Caron
 */

#include "__configure__.hpp"
#include <w32.sy/Token.hpp>

namespace w32 { namespace sy {

    class Token;

    class ImpersonationLevel
    {
        /* nested types. */
    public:
        typedef ::SECURITY_IMPERSONATION_LEVEL Value;

        /* class data. */
    public:
        static const ImpersonationLevel anonymous;
        static const ImpersonationLevel identification;
        static const ImpersonationLevel impersonation;
        static const ImpersonationLevel delegation;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        explicit ImpersonationLevel ( Value value );

        /* class methods. */
    public:
        ImpersonationLevel of ( const Token& token );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        bool operator== ( const ImpersonationLevel& other ) const;
        bool operator!= ( const ImpersonationLevel& other ) const;
    };

} }

#endif /* _w32_sy_ImpersonationLevel_hpp__ */
