#ifndef _w32_sy_ImpersonationLevel_hpp__
#define _w32_sy_ImpersonationLevel_hpp__

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

/*!
 * @file w32.sy/ImpersonationLevel.hpp
 * @brief User context impersonation services.
 */

#include "__configure__.hpp"
#include <w32.sy/Token.hpp>

namespace w32 { namespace sy {

    class Token;

    //! @addtogroup w32-sy
    //! @{

    class ImpersonationLevel
    {
        /* nested types. */
    public:
        typedef ::SECURITY_IMPERSONATION_LEVEL Value;

        /* class data. */
    public:
        static const ImpersonationLevel anonymous ();
        static const ImpersonationLevel identification ();
        static const ImpersonationLevel impersonation ();
        static const ImpersonationLevel delegation ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        ImpersonationLevel ( Value value );

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

    //! @}

} }

#endif /* _w32_sy_ImpersonationLevel_hpp__ */
