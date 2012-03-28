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

#include <w32.ldap/Session.hpp>

namespace {

    void abandon ( ::LDAP * object ) {}
    void destroy ( ::LDAP * object )
    {
        const ::ULONG result = ::ldap_unbind(object);
        if ( result != LDAP_SUCCESS )
        {
        }
    }

    ::LDAP * allocate ( ::LPWSTR host, ::ULONG port )
    {
        ::LDAP *const result = ::ldap_initW(host, port);
        if ( result == NULL )
        {
            const ::ULONG error =  LdapGetLastError();
            // ...
        }
        return (result);
    }

    ::LDAP * allocate ( ::LPCWSTR host, ::ULONG port )
    {
        return (allocate(const_cast<::LPWSTR>(host), port));
    }

    ::LDAP * allocate_ssl ( ::LPWSTR host, ::ULONG port )
    {
        ::LDAP *const result = ::ldap_sslinitW(host, port, TRUE);
        if ( result == NULL )
        {
            const ::ULONG error =  LdapGetLastError();
            // ...
        }
        return (result);
    }

    ::LDAP * allocate_ssl ( ::LPCWSTR host, ::ULONG port )
    {
        return (allocate_ssl(const_cast<::LPWSTR>(host), port));
    }

    void set_option ( ::LDAP * session, int option, const void * value )
    {
        const ::ULONG result = ::ldap_set_option
            (session, option, const_cast<void*>(value));
        if ( result != LDAP_SUCCESS )
        {
            // ...
        }
    }

    void get_option ( ::LDAP * session, int option, void * value )
    {
        const ::ULONG result = ::ldap_get_option(session, option, value);
        if ( result != LDAP_SUCCESS )
        {
            // ...
        }
    }

    unsigned short * nasty_cast ( const wchar_t * x )
    {
        return (reinterpret_cast<unsigned short*>(const_cast<wchar_t*>(x)));
    }

}

namespace w32 { namespace ldap {

    Session::Session ( const w32::string& host, bool secure )
        : myHandle(secure?
            ::allocate_ssl(host.data(), LDAP_SSL_PORT)
            :
            ::allocate(host.data(), LDAP_PORT))
    {

    }

    Session::Session ( const w32::string& host, uint16 port, bool secure )
        : myHandle(secure?
            ::allocate_ssl(host.data(), port)
            :
            ::allocate(host.data(), port))
    {
    }

    void Session::sign ( bool sign )
    {
        void *const value =
            sign? LDAP_OPT_ON : LDAP_OPT_OFF;
        ::set_option(myHandle, LDAP_OPT_SIGN, value);
    }

    bool Session::sign () const
    {
        ::ULONG value = 0;
        ::get_option(myHandle, LDAP_OPT_SIGN, &value);
        return (value != 0);
    }

    void Session::encrypt ( bool encrypt )
    {
        void *const value =
            encrypt? LDAP_OPT_ON : LDAP_OPT_OFF;
        ::set_option(myHandle, LDAP_OPT_ENCRYPT, value);
    }

    bool Session::encrypt () const
    {
        ::ULONG value = 0;
        ::get_option(myHandle, LDAP_OPT_ENCRYPT, &value);
        return (value != 0);
    }

    void Session::version ( ulong version )
    {
        ::set_option(myHandle, LDAP_OPT_VERSION, &version);
    }

    ulong Session::version () const
    {
        ::ULONG version = 0;
        ::get_option(myHandle, LDAP_OPT_VERSION, &version);
        return (version);
    }

    void Session::secure ( bool secure )
    {
        void *const value =
            secure? LDAP_OPT_ON : LDAP_OPT_OFF;
        ::set_option(myHandle, LDAP_OPT_SSL, value);
    }

    bool Session::secure () const
    {
        ::ULONG value = 0;
        ::get_option(myHandle, LDAP_OPT_SSL, &value);
        return (value != 0);
    }

    void Session::reconnect ( bool reconnect )
    {
        void *const value =
            reconnect? LDAP_OPT_ON : LDAP_OPT_OFF;
        ::set_option(myHandle, LDAP_OPT_AUTO_RECONNECT, value);
    }

    bool Session::reconnect () const
    {
        ::ULONG value = 0;
        ::get_option(myHandle, LDAP_OPT_AUTO_RECONNECT, &value);
        return (value != 0);
    }

    void Session::connect ()
    {
        const ::ULONG result = ::ldap_connect(myHandle, 0);
        if ( result != LDAP_SUCCESS )
        {
        }
    }

    void Session::authenticate ()
    {
        const ::ULONG result = ::ldap_bind_sW
            (myHandle, 0, 0, LDAP_AUTH_NTLM);
        if ( result != LDAP_SUCCESS )
        {
        }
    }

    void Session::authenticate ( const string& domain,
        const string& username, const string& password )
    {
        ::SEC_WINNT_AUTH_IDENTITY_W credentials;
        ::ZeroMemory(&credentials, sizeof(credentials));
        credentials.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
        credentials.User = ::nasty_cast(username.data());
        credentials.UserLength = username.size();
        credentials.Password = ::nasty_cast(password.data());
        credentials.PasswordLength = password.size();
        credentials.Domain = ::nasty_cast(domain.data());
        credentials.DomainLength = domain.size();
        
        const ::ULONG method = LDAP_AUTH_NTLM;
        const ::ULONG result = ::ldap_bind_sW
            (myHandle, 0, reinterpret_cast<::PWCHAR>(&credentials), method);
        if ( result != LDAP_SUCCESS )
        {
        }
    }

} }
