#ifndef _w32_sy_Identifier_hpp__
#define _w32_sy_Identifier_hpp__

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
 * @file w32.sy/Identifier.hpp
 * @brief Unique identifier for a user account on the network.
 */

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32/types.hpp>
#include <w32/Reference.hpp>

namespace w32 {

    class string;

}

namespace w32 { namespace sy {

    class Token;

    //! @addtogroup w32-sy
    //! @{

    /*!
     * @brief Unique identifier for a user account on the network.
     *
     * Identifies a user, group, and computer account. Every account on a
     * network is issued a unique SID when the account is first created.
     * Internal processes in Windows refer to an account's SID rather than the
     * account's user or group name.
     */
    class Identifier
    {
        /* nested types. */
    public:
        typedef Reference< ::PSID > Handle;

        /* class methods. */
    public:
        static Handle claim ( ::PSID object );
        static Handle proxy ( ::PSID object );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Identifier ( const string& value );
        Identifier ( ::PSID data );
        Identifier ( ::PSID data, ::DWORD size );
        Identifier ( const Identifier& other );

        /* methods. */
    public:
        Handle handle () const;
        bool valid () const;
        dword size () const;

        bool in ( const Token& token ) const;

        /* operators. */
    public:
        bool operator== ( const Identifier& other ) const;
        bool operator!= ( const Identifier& other ) const;

        operator string () const;
    };

    Identifier lookup ( const string& system, const string& account );

    //! @}

} }

#endif /* _w32_sy_Identifier_hpp__ */
