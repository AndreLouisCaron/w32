#ifndef _w32_ldap_Session_hpp__
#define _w32_ldap_Session_hpp__

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
#include <w32/Reference.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace ldap {

    class Session
    {
        /* nested types. */
    public:
        typedef Reference< ::LDAP* > Handle;

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Session ( const string& host, bool secure=false );
        Session ( const string& host, uint16 port, bool secure=false );

        /* methods. */
    public:
            // LDAP protocol version. Supports 1, 2 and 3. Default is 2.
        void version ( ulong version );
        ulong version () const;

            // NTLM & Kerberos digital signing.
        void sign ( bool sign );
        bool sign () const;

            // NTLM & Kerberos encryption.
        void encrypt ( bool encrypt );
        bool encrypt () const;

            // SSL encryption.
        void secure ( bool secure );
        bool secure () const;

           // Auto disconnect/reconnect. May help with long sessions
           // containing few operations?
        void reconnect ( bool reconnect );
        bool reconnect () const;

            // Automatically called by other ops, but it may help
            // diagnostics if called separately.
        void connect ();

            // Use current user's credentials for NTLM authentication.
        void authenticate ();

            // Use another user's credentials for NTLM authentication.
        void authenticate ( const string& domain,
            const string& username, const string& password );
    };

} }

#endif /* _w32_ldap_Session_hpp__ */
