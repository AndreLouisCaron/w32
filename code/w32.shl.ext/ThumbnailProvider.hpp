#ifndef _w32_shl_ext_ThumbnailProvider_hpp__
#define _w32_shl_ext_ThumbnailProvider_hpp__

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
#include <w32.shl/Stream.hpp>

namespace w32 { namespace shl { namespace ext {

    extern ::LONG GlobalObjectCount;

        /*!
         * @brief Shell extension that displays a thumbnail for files in the
         *    "thumbnail" mode of the explorer display.
         *
         * This is useful for files such as images: you may replace the standard
         * icon for the file type by a per-file preview method.
         */
    class ThumbnailProvider :
        public ::IInitializeWithStream,
        public ::IThumbnailProvider
    {
        /* nested types. */
    public:
        class Alpha;

        /* data. */
    private:
        volatile ::LONG myReferenceCount;
        com::Ptr< ::IStream > myStream;
        dword myMode;

        /* construction. */
    protected:
        ThumbnailProvider ()
            : myReferenceCount(1), myStream(), myMode(STGM_READ)
        {
            ::InterlockedIncrement(&GlobalObjectCount);
        }

        virtual ~ThumbnailProvider () {
            ::InterlockedDecrement(&GlobalObjectCount);
        }

        /* class methods. */
    public:
            /*!
             * @brief Shinks \c actual into \c requested, maintaining aspect
             *    ratio.
             */
        static w32::gdi::Size adjust (
            const w32::gdi::Size& actual, const w32::gdi::Size& requested
            );

        /* methods. */
    public:
        /* overrides. */
    public:
        ::ULONG __stdcall AddRef () {
            return (::InterlockedIncrement(&myReferenceCount));
        }

        ::ULONG __stdcall Release ()
        {
            if ( ::InterlockedDecrement(&myReferenceCount) == 0 )
            {
                delete this;
                return (0);
            }
            return (myReferenceCount);
        }

        ::HRESULT __stdcall QueryInterface (
            const ::GUID& guid, void ** object
            )
        {
            (*object) = 0;
            
            com::Guid::String iface(guid);
            if ( guid == IID_IUnknown ) {
                (*object) = static_cast< ::IUnknown* >(
                    dynamic_cast< ::IInitializeWithStream* >(this));
            }
            else if ( guid == IID_IInitializeWithStream ) {
                (*object) = dynamic_cast< ::IInitializeWithStream* >(this);
            }
            else if ( guid == IID_IThumbnailProvider ) {
                (*object) = dynamic_cast< ::IThumbnailProvider *>(this);
            }
            
            if ( (*object) != 0 ) {
                AddRef();
                return (S_OK);
            }
            
            return (E_NOINTERFACE);
        }

            /*!
             * @brief Indicates if the item for which a thumbnail can only be
             *    read from, not written to.
             *
             * Although some items might not be read-only, you should not
             * modify the files for which thumbnails are requested: by
             * definition, this is just a "peek" at the file.
             */
        bool readonly () const;
        com::Ptr< ::IStream > stream () const;

        virtual void compute (
            const w32::gdi::Size& size, dword depth
            ) = 0;
        virtual const w32::gdi::Bitmap& fetch () const = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall GetThumbnail (
            ::UINT width, ::HBITMAP * bitmap, ::WTS_ALPHATYPE * alphatype
            );

        virtual ::HRESULT __stdcall Initialize (
            ::IStream * stream, ::DWORD mode
            );
    };

    class ThumbnailProvider::Alpha
    {
        /* nested types. */
    public:
        typedef ::WTS_ALPHATYPE Value;

        /* class data. */
    public:
        static const Alpha unknown ();
        static const Alpha off ();
        static const Alpha on ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Alpha ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IInitializeWithStream > ()
{
    return (IID_IInitializeWithStream);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IThumbnailProvider > ()
{
    return (IID_IThumbnailProvider);
}

#endif /* _w32_shl_ext_IconOverlay_hpp__ */
