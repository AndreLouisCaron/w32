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

#include <w32.http/Group.hpp>
#include <w32.http/Queue.hpp>
#include <w32.http/Session.hpp>
#include <w32/Error.hpp>

namespace {

    ::HTTP_URL_GROUP_ID allocate ( ::HTTP_SERVER_SESSION_ID session )
    {
        ::HTTP_URL_GROUP_ID handle = 0;
        const ::ULONG result = ::HttpCreateUrlGroup(session, &handle, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpCreateUrlGroup, result);
        }
        std::cout << "  -- queue handle: " << handle << std::endl;
        return (handle);
    }

    void abandon ( ::HTTP_URL_GROUP_ID object ) {}
    void destroy ( ::HTTP_URL_GROUP_ID object )
    {
        const ::ULONG result = ::HttpCloseUrlGroup(object);
        if ( result != NO_ERROR ) {
            std::cerr << "[[[ " << w32::Error(result) << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace http {

    Group::Handle Group::claim ( ::HTTP_URL_GROUP_ID object )
    {
        return (Handle(object, &::destroy));
    }

    Group::Handle Group::proxy ( ::HTTP_URL_GROUP_ID object )
    {
        return (Handle(object, &::abandon));
    }

    Group::Group ( Session& session )
        : myHandle(claim( ::allocate(session.handle()) ))
    {
        std::cout << "  -- queue handle: " << handle() << std::endl;
    }

    const Group::Handle& Group::handle () const
    {
        return (myHandle);
    }

    void Group::bind ( Queue& queue )
    {
        ::HTTP_BINDING_INFO binding;
        binding.Flags.Present = 1;
        binding.RequestQueueHandle = queue.handle();
        
        std::cout << "  -- queue handle: " << queue.handle() << std::endl;
        std::cout << "  -- group handle: " << handle() << std::endl;
        const ::ULONG result = ::HttpSetUrlGroupProperty
            (handle(), HttpServerBindingProperty, &binding, sizeof(binding));
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpSetUrlGroupProperty, result);
        }
    }

    void Group::add ( const string& url, Context context )
    {
        const ::ULONG result = ::HttpAddUrlToUrlGroup
            (handle(), url.data(), context, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpCreateUrlGroup, result);
        }
    }

    void Group::add ( const string& url )
    {
        add(url, static_cast<Context>(0));
    }

    void Group::add ( const string& url, void * context )
    {
        add(url, static_cast<Context>(reinterpret_cast<intptr>(context)));
    }

    void Group::del ( const string& url )
    {
        const ::ULONG result =
            ::HttpRemoveUrlFromUrlGroup(handle(), url.data(), 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpRemoveUrlFromUrlGroup, result);
        }
    }

    void Group::clear ()
    {
        const ::ULONG result = ::HttpRemoveUrlFromUrlGroup
            (handle(), 0, HTTP_URL_FLAG_REMOVE_ALL);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpRemoveUrlFromUrlGroup, result);
        }
    }

} }
