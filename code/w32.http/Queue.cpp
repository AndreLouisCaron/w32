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

#include <w32.http/Queue.hpp>
#include <w32.http/Request.hpp>
#include <w32/Error.hpp>

namespace {

    ::HANDLE allocate_v1 ()
    {
        ::HANDLE handle = 0;
        const ::ULONG result = ::HttpCreateHttpHandle(&handle, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpCreateHttpHandle, result);
        }
        return (handle);
    }

    ::HANDLE allocate_v2 ( const ::HTTPAPI_VERSION& version )
    {
        ::HANDLE handle = 0;
        const ::ULONG result =
            ::HttpCreateRequestQueue(version, 0, 0, 0, &handle);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpCreateRequestQueue, result);
        }
        return (handle);
    }

    ::HANDLE allocate ( const w32::http::Library::Version& version )
    {
        if ( version == w32::http::Library::Version::_1() ) {
            return (allocate_v1());
        }
        return (allocate_v2(version.data()));
    }

    void abandon ( ::HANDLE object ) {}
    void release ( ::HANDLE object )
    {
        const ::BOOL result = ::CloseHandle(object);
        if ( result == FALSE ) {
            const w32::Error error(::GetLastError());
            std::cerr << "[[[ " << error << " ]]]" << std::endl;
        }
    }

}

namespace w32 { namespace http {

    Queue::Handle Queue::claim ( ::HANDLE object )
    {
        return (Handle(object, &::release));
    }

    Queue::Handle Queue::proxy ( ::HANDLE object )
    {
        return (Handle(object, &::abandon));
    }

    Queue::Queue ( const Library& library )
        : myHandle(claim( ::allocate(library.version()) ))
    {
    }

    const Queue::Handle& Queue::handle () const
    {
        return (myHandle);
    }

    void Queue::shutdown ()
    {
        const ::ULONG result = ::HttpShutdownRequestQueue(handle());
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpShutdownRequestQueue, result);
        }
    }

    void Queue::get ( Request& request )
    {
        ::HTTP_REQUEST_V2& data = request.data();
        const ::ULONG size = request.size();
        
        std::cout << "  -- data: " << &data << std::endl;
        std::cout << "  -- size: " << size << std::endl;
        ::ULONG received = 0;
        const ::ULONG result = ::HttpReceiveHttpRequest
            (handle(), HTTP_NULL_ID, 0, &data, size, &received, 0);
        if ( result != NO_ERROR )
        {
            if ( result == ERROR_MORE_DATA )
            {
                return;
            }
            UNCHECKED_WIN32C_ERROR(HttpReceiveHttpRequest, result);
        }
    }

    bool Queue::get ( Request::Id id, Request &request )
    {
        ::HTTP_REQUEST_V2 data = request.data();
        const ::ULONG size = request.size();
        
        ::ULONG received = 0;
        const ::ULONG result = ::HttpReceiveHttpRequest
            (handle(), id, 0, &data, size, &received, 0);
        if ( result != NO_ERROR )
        {
            if ( result == ERROR_MORE_DATA )
            {
            }
            if ((result == ERROR_CONNECTION_INVALID) && !HTTP_IS_NULL_ID(&id))
            {
                    // MSDN sample program describes this situation as:
                    //   "The TCP connection was corrupted by the peer when
                    //    attempting to handle a request with more buffer.
                    //    Continue to the next request."
                return (false);
            }
            UNCHECKED_WIN32C_ERROR(HttpReceiveHttpRequest, result);
        }
        return (true);
    }

    void Queue::put ( const Request& request, Response& response )
    {
        put(request.id(), response);
    }

    void Queue::put ( const Request::Id& request, Response& response )
    {
        std::cout << "  -- chunk: " << response.data().pEntityChunks->FromMemory.pBuffer << std::endl;
        ::ULONG sent = 0;
        const ::ULONG result = ::HttpSendHttpResponse
            (handle(), request, 0, &response.data(), 0, &sent, 0, 0, 0, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpSendHttpResponse, result);
        }
    }

    void Queue::cache ( const string& url, Chunk& chunk )
    {
        ::HTTP_CACHE_POLICY policy;
        policy.Policy = HttpCachePolicyUserInvalidates;
        policy.SecondsToLive = 0;
        
        const ::ULONG result = ::HttpAddFragmentToCache
            (handle(), url.data(), &chunk.data(), &policy, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpAddFragmentToCache, result);
        }
    }

    void Queue::cache ( const string& url, Chunk& chunk, ulong seconds )
    {
        ::HTTP_CACHE_POLICY policy;
        policy.Policy = HttpCachePolicyTimeToLive;
        policy.SecondsToLive = seconds;
        
        const ::ULONG result = ::HttpAddFragmentToCache
            (handle(), url.data(), &chunk.data(), &policy, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpAddFragmentToCache, result);
        }
    }

    void Queue::clear ( const string& url, bool recursive )
    {
        const ::ULONG flags =
            recursive? HTTP_FLUSH_RESPONSE_FLAG_RECURSIVE : 0;
        
        const ::ULONG result = ::HttpFlushResponseCache
            (handle(), url.data(), flags, 0);
        if ( result != NO_ERROR )
        {
            UNCHECKED_WIN32C_ERROR(HttpFlushResponseCache, result);
        }
    }

} }
