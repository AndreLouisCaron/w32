#ifndef _w32_io_Stream_hpp__
#define _w32_io_Stream_hpp__

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
 * @file w32.io/Stream.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace io {

    class Transfer;

    /*!
     * @ingroup w32-io
     * @brief Base class for input/output streams.
     *
     * Provides access to the stream's handle, for low-level manipulation.
     */
    class Stream :
        public Object
    {
        /* nested types. */
    public:
        class Position;
        class Size;
        class Type;

        class Builder;

        /* construction. */
    public:
        explicit Stream ( const Handle& handle );

         /* methods. */
     public:
        Size size () const;
        Position position () const;
        void position ( const Position& value ) const;

        /*!
         * @brief Cancel all pending I/O operations for the stream.
         *
         * @note Prior to Windows Vista, this only cancels pending I/O
         *  operations issued by the calling thread.
         */
        void cancel ();

        /*!
         * @brief Cancel a specific pending I/O request.
         */
        bool cancel ( Transfer& transfer );

        /*!
         * @brief Block until the transfer finishes.
         */
        dword finish ( Transfer& transfer );
     };

    class Stream::Type
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* class data. */
    public:
        static const Type character ();
        static const Type disk ();
        static const Type remote ();
        static const Type ipc ();
        static const Type unknown ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Type ( Value value );

        /* class methods. */
    public:
        static Type of ( const Stream& stream );

        /* methods. */
    public:
        Value value () const;
    };

    class Stream::Position
    {
        /* nested types. */
    public:
        typedef ::LARGE_INTEGER Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Position ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value value () const {
            return (myValue);
        }
    };

    class Stream::Size
    {
        /* nested types. */
    public:
        typedef ::LARGE_INTEGER Value;

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
        Size ( const Value& value )
            : myValue(value)
        {}

        /* methods. */
    public:
        Value value () const {
            return (myValue);
        }
    };

    class Stream::Builder
    {
        /* data. */
    private:
        ::DWORD myDesiredAccess;
        ::DWORD myShareMode;
        ::LPSECURITY_ATTRIBUTES mySecurityAttributes;
        ::DWORD myCreationDisposition;
        ::DWORD myFlagsAndAttributes;
        ::HANDLE myTemplateFile;

        /* construction. */
    public:
        Builder ();

        /* methods. */
    public:
        Builder& generic_read ();
        Builder& generic_write ();

        Builder& share_read ();
        Builder& share_write ();
        Builder& share_delete ();

        Builder& create_always ();
        Builder& create_new ();
        Builder& open_always ();
        Builder& open_existing ();
        Builder& truncate_existing ();

        Builder& no_buffering ();
        Builder& overlapped ();
        Builder& sequential_scan ();
        Builder& write_through ();

        Stream::Handle open (const string& path) const;
    };

} }

#endif /* _w32_io_Stream_hpp__ */
