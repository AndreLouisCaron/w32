#ifndef _w32_cr_Buffer_hpp__
#define _w32_cr_Buffer_hpp__

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
#include <w32/types.hpp>

namespace w32 { namespace cr {

    //! @addtogroup w32-cr
    //! @{

    template<dword N>
    class Buffer
    {
        /* data. */
    private:
        ::SecBufferDesc myDescriptor;
        ::SecBuffer myBuffers[N];
        ::DWORD myCapacity[N];

        /* construction. */
    public:
        Buffer ()
        {
                // Fill buffer description.
            myDescriptor.ulVersion = SECBUFFER_VERSION;
            myDescriptor.cBuffers  = N;
            myDescriptor.pBuffers  = myBuffers;
            
                // Let derived classes fill buffer content.
            ::ZeroMemory(myBuffers,  sizeof(myBuffers) );
            ::ZeroMemory(myCapacity, sizeof(myCapacity));
        }

        /* operators. */
    public:
        ::SecBuffer& operator[] ( dword i )
        {
            return (myBuffers[i]);
        }

        const ::SecBuffer& operator[] ( dword i ) const
        {
            return (myBuffers[i]);
        }

        ::PSecBufferDesc operator* ()
        {
            return (&myDescriptor);
        }

        /* methods. */
    public:
        ::SecBuffer& buffer ( dword i )
        {
            return (myBuffers[i]);
        }

        dword capacity ( dword i ) const
        {
            return (myCapacity[i]);
        }

        bool isstream ( dword i ) const
        {
            return (myBuffers[i].BufferType == SECBUFFER_DATA);
        }

        void empty ( dword i )
        {
            buffer(i).BufferType = SECBUFFER_EMPTY;
            buffer(i).cbBuffer   = 0;
            buffer(i).pvBuffer   = 0;
        }

        void token ( dword i )
        {
            buffer(i).BufferType = SECBUFFER_TOKEN;
            buffer(i).cbBuffer = 0;
            buffer(i).pvBuffer = 0;
        }

        void stream ( dword i, dword capacity )
        {
            buffer(i).BufferType = SECBUFFER_DATA;
            buffer(i).cbBuffer = 0;
            buffer(i).pvBuffer = operator new(capacity);
            myCapacity[i] = capacity;
        }

        void header ( dword i, dword capacity )
        {
            buffer(i).BufferType = SECBUFFER_STREAM_HEADER;
            buffer(i).cbBuffer = capacity;
            buffer(i).pvBuffer = operator new(capacity);
            myCapacity[i] = capacity;
        }

        void footer ( dword i, dword capacity )
        {
            buffer(i).BufferType = SECBUFFER_STREAM_TRAILER;
            buffer(i).cbBuffer = capacity;
            buffer(i).pvBuffer = operator new(capacity);
            myCapacity[i] = capacity;
        }

        void stuff ( dword i, dword capacity )
        {
            buffer(i).cbBuffer = 0;
            buffer(i).pvBuffer = operator new(capacity);
            myCapacity[i] = capacity;
        }

        void clear ( dword i )
        {
            buffer(i).cbBuffer = 0;
        }

        void erase ( dword i )
        {
            const ::SECURITY_STATUS status =
                ::FreeContextBuffer(buffer(i).pvBuffer);
            if ( status != SEC_E_OK )
            {
                // ...
            }
            buffer(i).cbBuffer = 0;
            buffer(i).pvBuffer = 0;
        }

        void store ( dword i, void * data, dword size )
        {
            ::memcpy(buffer(i).pvBuffer, data, size);
            buffer(i).cbBuffer = size;
        }

        dword fetch ( dword i, void * data, dword size )
        {
            ::memcpy(data, buffer(i).pvBuffer, buffer(i).cbBuffer);
            return (buffer(i).cbBuffer);
        }
    };

    //! @}

} }

#endif /* _w32_cr_Buffer_hpp__ */
